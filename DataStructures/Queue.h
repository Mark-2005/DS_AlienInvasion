////
//// Created by ahmed on 06/03/2024.
////
#ifndef DS_ALIENINVASION_QUEUE_H
#define DS_ALIENINVASION_QUEUE_H
#include "Node.h"
#include "../Units/Unit.h"
#include "QueueADT.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedQueue:public QueueADT<T>
{
protected :
    Node<T>* backPtr;
    Node<T>* frontPtr;
    int count;
public :
    LinkedQueue();
    bool isEmpty() const ;
    bool enqueue(const T& newEntry);
    bool dequeue(T& frntEntry);
    bool peek(T& frntEntry)  const;
    void printQueue() const;
    int getCount() const;
    LinkedQueue(const LinkedQueue<T> & LQ);
    ~LinkedQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
    backPtr=nullptr;
    frontPtr=nullptr;
    count=0;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return (frontPtr==nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue( const T& newEntry)
{
    Node<T>* newNodePtr = new Node<T>(newEntry);
    // Insert the new node
    if (isEmpty()) {    //special case if this is the first node to insert
        frontPtr = newNodePtr; // The queue is empty
    } else {
        backPtr->setNext(newNodePtr); // The queue was not empty
    }

    backPtr = newNodePtr; // New node is the last node now
    count++;
    return true ;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>:: dequeue(T& frntEntry)
{
    if(isEmpty())
        return false;

    Node<T>* nodeToDeletePtr = frontPtr;
    frntEntry = frontPtr->getItem();
    frontPtr = frontPtr->getNext();
    // Queue is not empty; remove front
    if (nodeToDeletePtr == backPtr)     // Special case: last node in the queue
        backPtr = nullptr;

    // Free memory reserved for the dequeued node
    delete nodeToDeletePtr;
    count--;

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

template <typename T>
bool LinkedQueue<T>:: peek(T& frntEntry) const
{
    if(isEmpty())
        return false;

    frntEntry = frontPtr->getItem();
    return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    //Note that the cout statements here is just for learning purpose
    //They should be normally removed from the destructor
//    cout<<"\nStarting LinkedQueue destructor...";
//    cout<<"\nFreeing all nodes in the queue...";

    //Free all nodes in the queue
    T temp;
    while(dequeue(temp));

//    cout<<"\n Is LinkedQueue Empty now?? ==> "<<boolalpha<<isEmpty();
//    cout<<"\nEnding LinkedQueue destructor..."<<endl;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
void LinkedQueue<T>::printQueue() const {
    Node<T>*ptr=frontPtr;
    if(!isEmpty())cout<<"[ "; else return;
    while(ptr!= nullptr){
        cout<<*(ptr->getItem());
        ptr=ptr->getNext();
    }
    cout<<"]"<<endl;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> & LQ)
{
    frontPtr = backPtr = nullptr;
    Node<T>* NodePtr = LQ.frontPtr;	//start at the front node in LQ
    while (NodePtr)
    {
        enqueue(NodePtr->getItem());	//get data of each node and enqueue it in this queue
        NodePtr = NodePtr->getNext();
    }
}

template <typename T>
int LinkedQueue<T>::getCount() const {return count;}

#endif