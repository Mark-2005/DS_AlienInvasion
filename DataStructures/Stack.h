#pragma once
#include "Node.h"
#include "StackADT.h"
#include<iostream>

template<typename T>
class Stack: public StackADT<T> {
private:
    Node<T>* Top;
    int count;
public:
    Stack();
    bool isEmpty() const;
    bool push(const T& newEntry);
    bool pop(T& newEntry);
    bool peek(T& newEntry) const;
    void printStack() const;
    int getCount() const;
    ~Stack();

};

template <typename T>
Stack<T>::Stack(){Top=nullptr;count=0;}

template <typename T>
bool Stack<T>::isEmpty() const
{
    if(Top==nullptr)
        return true;
    else
        return false;
}

template <typename T>
bool Stack<T>::push(const T& newEntry)
{
    Node<T>* temp= new Node<T>();
    temp->setItem(newEntry);
    if(Top==nullptr){
        Top=temp;
        count++;
        return true;
    }else {
        temp->setNext(Top);
        Top = temp;
        count++;
        return true;
    }
}

template <typename T>
bool Stack<T>::pop(T& TopEntry)
{
    if(Top==NULL)
    {
        return false;
    }
    else
    {
        Node<T> *temp;
        temp=Top;
        temp->setItem(Top->getItem());
        Top=Top->getNext();
        TopEntry=temp->getItem();
        count--;
        return true;
    }
}

template <typename T>
bool Stack<T>::peek(T& TopEntry) const
{
    if(Top==NULL)
        return false;
    else
    {
        TopEntry=Top->getItem();
    }
    return true;
}

template <typename T>
void Stack<T>::printStack() const
{
    Node<T>* temp=Top;
    if(!isEmpty())cout<<"[ "; else return;
    while(temp!=NULL)
    {
        std::cout<<*(temp->getItem());
        temp=temp->getNext();
    }
    std::cout<<"]"<<std::endl;
}

template <typename T>
Stack<T>::~Stack() {
    //Note that the cout statements here is just for learning purpose
    //They should be normally removed from the destructor
//    cout << "\nStarting Stack destructor...";
//    cout << "\nFreeing all nodes in the stack...";

    //Free all nodes in the queue
    T temp;
    while (pop(temp));

//    cout << "\n Is Stack Empty now?? ==> " << boolalpha << isEmpty();
//    cout << "\nEnding Stack destructor..." << endl;
}

template <typename T>
int Stack<T>::getCount() const {return count;}