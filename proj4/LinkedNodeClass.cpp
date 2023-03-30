#include "LinkedNodeClass.h"

#include <iostream>
using namespace std;

LinkedNodeClass::LinkedNodeClass(LinkedNodeClass* inPrev, 
                                 const int& inVal, 
                                 LinkedNodeClass* inNext)
{
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}

int LinkedNodeClass::getValue() const
{
  return nodeVal;
}

LinkedNodeClass* LinkedNodeClass::getNext() const
{
  return nextNode;
}

LinkedNodeClass* LinkedNodeClass::getPrev() const
{
  return prevNode;
}

void LinkedNodeClass::setNextPointerToNull()
{
  nextNode = 0;
}

void LinkedNodeClass::setPreviousPointerToNull()
{
  prevNode = 0;
}

void LinkedNodeClass::setBeforeAndAfterPointers()
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
