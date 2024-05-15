#ifndef DS_ALIENINVASION_DEQUEUE_H
#define DS_ALIENINVASION_DEQUEUE_H

#include "Queue.h"
#include "Node.h"

template<typename T>
class DEqueue : public LinkedQueue<T> {
public:
    bool enqueueFront(const T& newEntry);
    bool dequeueBack(T& backEntry);
    bool peekBack(T& backEntry) const;
    int getCount() const;
};

template <typename T>
bool DEqueue<T>::peekBack(T& backEntry) const
{
    if(this->isEmpty())
        return false;

    backEntry = this->backPtr->getItem();
    return true;
}

template <typename T>
bool DEqueue<T>:: dequeueBack(T& backEntry)
{
    if(this->isEmpty())
        return false;

    Node<T>* nodeToDeletePtr = this->backPtr;
    backEntry=this->backPtr->getItem();

    if(this->backPtr==this->frontPtr){
        this->frontPtr=nullptr;
        this->backPtr=nullptr;
    } else {
        Node<T>*currentPtr=this->frontPtr;
        while (currentPtr->getNext() != this->backPtr) {
            currentPtr = currentPtr->getNext();
        }
        currentPtr->setNext(nullptr);
        this->backPtr = currentPtr;
    }
    this->count--;
    return true;
}

template <typename T>
bool DEqueue<T>::enqueueFront(const T &newEntry) {
    Node<T>* newNodePtr = new Node<T>(newEntry);
    // Insert the new node
    if (this->isEmpty()) {    //special case if this is the first node to insert
        this->frontPtr = newNodePtr; // The queue is empty
        this->backPtr = newNodePtr; // New node is the last node now
    } else {
        newNodePtr->setNext(this->frontPtr); // The queue was not empty
        this->frontPtr=newNodePtr;
    }

    this->count++;
    return true ;
}

template <typename T>
int DEqueue<T>::getCount() const {return this->count;}

#endif //DS_ALIENINVASION_DEQUEUE_H
