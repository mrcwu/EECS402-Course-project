#include "LIFOStackClass.h"

#include "LinkedNodeClass.h"

#include <iostream>
using namespace std;

LIFOStackClass::LIFOStackClass()
{
  head = 0;
  tail = 0;
}

LIFOStackClass::~LIFOStackClass()
{
  clear();
}

void LIFOStackClass::push(const int& newItem)
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

bool LIFOStackClass::pop(int& outItem)
{
  // case 1: if there is 0 item in current list (empty list)
  if (head == 0)
  {
    return false;
  }
  // case 2: if there is only 1 item in the current list
  else if (head == tail) // if noting is before the head item
  {
    // set the output
    outItem = head->getValue();
    // reset the list to empty list
    head = 0;
    tail = 0;
    // set the output
    return true;
  }
  // case 3: if there are more than 1 item in the list
  else
  {
    outItem = head->getValue();
    // set the new head to the second one
    head = head->getNext();
    // delete the old head
    delete head->getPrev();
    // reset the new head's prevPointer to Null
    head->setPreviousPointerToNull();

    return true;
  }
}

void LIFOStackClass::print() const
{
  LinkedNodeClass* tempPtr = head;
  // cout the items from the head to the tail (same as FIFO)
  while (tempPtr != 0)
  {
    cout << tempPtr->getValue() << " ";
    tempPtr = tempPtr->getNext();
  }
  cout << endl;
}

int LIFOStackClass::getNumElems() const
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

void LIFOStackClass::clear()
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