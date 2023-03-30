#include "FIFOQueueClass.h"

#include "LinkedNodeClass.h"

#include <iostream>
using namespace std;

template <class T>
FIFOQueueClass<T>::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

template <class T>
FIFOQueueClass<T>::~FIFOQueueClass()
{
  clear();
}

template <class T>
void FIFOQueueClass<T>::enqueue(const T& newItem)
{
  LinkedNodeClass<T>* tempPtr;
  // case 1: if there is 0 item in current list (empty list)
  if (head == 0)
  {
    tempPtr = new LinkedNodeClass<T>(0, newItem, 0);
    head = tempPtr;
    tail = tempPtr;
  }
  // case 2: if there are at least 1 item in the list
  else
  {
    tempPtr = new LinkedNodeClass<T>(0, newItem, head);
    tempPtr->setBeforeAndAfterPointers();
    head = tempPtr;
  }
}

template <class T>
bool FIFOQueueClass<T>::dequeue(T& outItem)
{
  // case 1: if there is 0 item in current list (empty list)
  if (tail == 0)
  {
    return false;
  }
  // case 2: if there is only 1 item in the current list
  else if (tail->getPrev() == 0) // if noting is before the tail item
  {
    // set the output
    outItem = tail->getValue();
    // clear list to empty list
    clear();
    // set the output
    return true;
  }
  // case 3: if there are more than 1 item in the list
  else
  {
    outItem = tail->getValue();
    // set the new tail to the second last one
    tail = tail->getPrev();
    // delete the old tail
    delete tail->getNext();
    // reset the new tail's nextPointer to Null
    tail->setNextPointerToNull();

    return true;
  }
}

template <class T>
void FIFOQueueClass<T>::print() const
{
  LinkedNodeClass<T>* tempPtr = head;
  // cout the items from the head to the tail
  while (tempPtr != 0)
  {
    cout << tempPtr->getValue() << " ";
    tempPtr = tempPtr->getNext();
  }
  cout << endl;
}

template <class T>
int FIFOQueueClass<T>::getNumElems() const
{
  LinkedNodeClass<T>* tempPtr = head;
  int counting = 0;

  while (tempPtr != 0)
  {
    tempPtr = tempPtr->getNext();
    counting += 1;
  }

  return counting;
}

template <class T>
void FIFOQueueClass<T>::clear()
{
  LinkedNodeClass<T>* toDeletePtr = head;
  LinkedNodeClass<T>* tempPtr = head;

  while (toDeletePtr != 0)
  {
    tempPtr = tempPtr->getNext();
    delete toDeletePtr;
    toDeletePtr = tempPtr;
  }
  // reset head and tail pointers
  head = 0;
  tail = 0;
}