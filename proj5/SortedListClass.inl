#include "SortedListClass.h"

#include "LinkedNodeClass.h"

#include <iostream>
using namespace std;

template <class T>
SortedListClass<T>::SortedListClass()
{
  head = 0;
  tail = 0;
}

template <class T>
SortedListClass<T>::SortedListClass(const SortedListClass<T>& rhs)
{
  head = 0;
  LinkedNodeClass<T>* tempPtr = rhs.head;
  // insert values from the head of rhs
  while (tempPtr != 0) // the last item's nextNode pointer is Null
  {
    insertValue(tempPtr->getValue());
    // Set tempPointer to the nextNode of current node
    tempPtr = tempPtr->getNext();
  }
}

template <class T>
SortedListClass<T>::~SortedListClass()
{
  clear();
}

template <class T>
void SortedListClass<T>::clear()
{
  LinkedNodeClass<T>* toDeletePtr = head;
  LinkedNodeClass<T>* tempPtr = head;
  while(toDeletePtr != 0) 
  {
    tempPtr = toDeletePtr->getNext();
    delete toDeletePtr;
    toDeletePtr = tempPtr;
  }
  // reference: 
  // https://stackoverflow.com/questions/10152150/c-linked-list-memory-leak

  // delete head and tail pointers
  head = 0;
  tail = 0;
}

template <class T>
void SortedListClass<T>::insertValue(const T& valToInsert)
{
  LinkedNodeClass<T>* insertNodePtr;

  // case 1: if there is 0 item in current list (empty list)
  if (head == 0)
  {
    insertNodePtr = new LinkedNodeClass<T>(0, valToInsert, 0);
    head = insertNodePtr;
    tail = insertNodePtr;
  }

  // case 2: if the valToInsert is smaller than the current head 
  // (insert to the first place)
  else if (valToInsert < head->getValue())
  {
    insertNodePtr = new LinkedNodeClass<T>(0, valToInsert, head);
    head = insertNodePtr;
    insertNodePtr->setBeforeAndAfterPointers();
  }

  // case 3: if the valToInsert is equal/greater than the current last 
  // (insert to the last place)
  else if (valToInsert >= tail->getValue())
  {
    insertNodePtr = new LinkedNodeClass<T>(tail, valToInsert, 0);
    tail = insertNodePtr;
    insertNodePtr->setBeforeAndAfterPointers();
  }

  // case 4: if the valToInsert is between the current first and last
  // (insert in the middle)
  else
  {
    LinkedNodeClass<T>* tempPtr = head;

    // a loop to search the right location, it will keep going until it get to 
    // the node location to insert in (the original node location that has a  
    // value is not only greater than the value 1 step before but also greater  
    // than the insertNode's value)
    while (valToInsert >= tempPtr->getValue())
    {
      tempPtr = tempPtr->getNext();
    }

    insertNodePtr = new LinkedNodeClass<T>(tempPtr->getPrev(), 
                                           valToInsert, 
                                           tempPtr);
    insertNodePtr->setBeforeAndAfterPointers();
  }
}

template <class T>
void SortedListClass<T>::printForward() const
{
  LinkedNodeClass<T>* tempPtr = head;

  cout << "Forward List Contents Follow:" << endl;

  while (tempPtr != 0)
  {
    cout << "  " << tempPtr->getValue() << endl;
    tempPtr = tempPtr->getNext(); 
  }

  cout << "End Of List Contents" << endl;
}

template <class T>
void SortedListClass<T>::printBackward() const
{
  LinkedNodeClass<T>* tempPtr = tail;

  cout << "Backward List Contents Follow:" << endl;

  while (tempPtr != 0)
  {
    cout << "  " << tempPtr->getValue() << endl;
    tempPtr = tempPtr->getPrev();
  }

  cout << "End Of List Contents" << endl;
}

template <class T>
bool SortedListClass<T>::removeFront(T& theVal)
{
  // case 1: if there is 0 item in current list (empty list)
  if (head == 0)
  {
    return false;
  }

  // case 2: if there is only 1 item in the current list
  else if (head->getNext() == 0)
  {
    theVal = head->getValue();
    // clear the list
    clear();

    return true;
  }
  // case 3: it's a normal list
  else
  {
    theVal = head->getValue();
    // reset the head to the second one
    head = head->getNext();
    // delete the previous head
    delete head->getPrev();
    // update the new head, set the new head's prevNodePtr to Null
    head->setPreviousPointerToNull();

    return true;
  }
}

template <class T>
bool SortedListClass<T>::removeLast(T& theVal)
{
  // case 1: if there is 0 item in current list (empty list)
  if (tail == 0)
  {
    return false;
  }

  // case 2: if there is only 1 item in the current list
  else if (tail->getPrev() == 0)
  {
    theVal = tail->getValue();
    // clear the list
    clear();

    return true;
  }
  // case 3: it's a normal list
  else
  {
    theVal = tail->getValue();
    // reset the tail to the second one
    tail = tail->getPrev();
    // delete the previous tail
    delete tail->getNext();
    // update the new tail, set the new tail's nextNodePtr to Null
    tail->setNextPointerToNull();

    return true;
  }
}

template <class T>
int SortedListClass<T>::getNumElems() const
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
bool SortedListClass<T>::getElemAtIndex(const int index, T& outVal) const
{
    // case 1: if it's an empty list or the given index is out of range
    if ((head == 0) || (index < 0) || (index >= getNumElems()))
    {
        return false;
    }
    // case 2: normal stituation
    else
    {
      LinkedNodeClass<T>* tempPtr = head;
      // this forloop will keep indexing to the next until it meet the position
      // number
      for (int i = 0; i < index; i++)
      {
        tempPtr = tempPtr->getNext();
      }
      // output
      outVal = tempPtr->getValue();
      return true;
    }
}
