#include "LinkedNodeClass.h"

#include <iostream>
using namespace std;

template <class T>
LinkedNodeClass<T>::LinkedNodeClass(LinkedNodeClass<T>* inPrev, 
                                    const T& inVal, 
                                    LinkedNodeClass<T>* inNext)
{
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}

template <class T>
T LinkedNodeClass<T>::getValue() const
{
  return nodeVal;
}

template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getNext() const
{
  return nextNode;
}

template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getPrev() const
{
  return prevNode;
}

template <class T>
void LinkedNodeClass<T>::setNextPointerToNull()
{
  nextNode = 0;
}

template <class T>
void LinkedNodeClass<T>::setPreviousPointerToNull()
{
  prevNode = 0;
}

template <class T>
void LinkedNodeClass<T>::setBeforeAndAfterPointers()
{
  // case 1: if it's the first node of the sequence
  if (prevNode == 0) 
  {
    // if this node is not the last (nextNode is not Null), 
    // it will set "nextNode's prevNode" to this node.
    // if this node is the last, then do nothing.
    if (nextNode != 0)
    {
      nextNode->prevNode = this;
    }
  }

  // case 2: if it's not the first node of the sequence
  else
  {
    // if this node is not the last (nextNode is not Null), 
    // it will set "nextNode's prevNode" to this node.
    // if this node is the last, then do nothing.
    if (nextNode != 0)
    {
      nextNode->prevNode = this;
    }

    // set "prevNode's nextNode" to this node.
    prevNode->nextNode = this;
  }

}
