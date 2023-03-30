#include "FIFOQueueClass.h"

#include "LinkedNodeClass.h"

#include <iostream>
using namespace std;
FIFOQueueClass::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

FIFOQueueClass::~FIFOQueueClass()
{
  clear();
}

void FIFOQueueClass::enqueue(const int& newItem)
{
  LinkedNodeClass* tempPtr;
  // case 1: if there is 0 item in current list (empty list)
  if (head == 0)
  {
    tempPtr = new LinkedNodeClass(0, newItem, 0);
    head = tempPtr;
    tail = tempPtr;
  }
  // case 2: if there are at least 1 item in the list
  else
  {
    tempPtr = new LinkedNodeClass(0, newItem, head);
    tempPtr->setBeforeAndAfterPointers();
    head = tempPtr;
  }
}

bool FIFOQueueClass::dequeue(int& outItem)
{
  // case 1: if there is 0 item in current list (empty list)
  if (tail == 0)
  {
    return false;
  }
  // case 2: if there is only 1 item in the current list
  else if (head == tail) // if noting is before the tail item
  {
    // set the output
    outItem = tail->getValue();
    // reset the list to empty list
    head = 0;
    tail = 0;
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

void FIFOQueueClass::print() const
{
  LinkedNodeClass* tempPtr = head;
  // cout the items from the head to the tail
  while (tempPtr != 0)
  {
    cout << tempPtr->getValue() << " ";
    tempPtr = tempPtr->getNext();
  }
  cout << endl;
}

int FIFOQueueClass::getNumElems() const
{
  LinkedNodeClass* tempPtr = head;
  int counting = 0;

  while (tempPtr != 0)
  {
    tempPtr = tempPtr->getNext();
    counting += 1;
  }

  return counting;
}

void FIFOQueueClass::clear()
{
  LinkedNodeClass* toDeletePtr = head;
  LinkedNodeClass* tempPtr = head;

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