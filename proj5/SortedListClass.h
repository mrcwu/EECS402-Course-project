#ifndef _SORTEDLISTCLASS_H_
#define _SORTEDLISTCLASS_H_

#include "LinkedNodeClass.h"

#include <iostream>
using namespace std;

//Programmer: Conan Wu
//Date: Dec 2022
//Purpose:
//   1. Adopt the sortedListClass for Project 5
//   2. The sorted list class does not store any data directly. Instead,
//      it contains a collection of LinkedNodeClass objects, each of which
//      contains one element.

template <class T>
class SortedListClass
{
private:
  LinkedNodeClass<T>* head; //Points to the first node in a list, or NULL
  //if list is empty.
  LinkedNodeClass<T>* tail; //Points to the last node in a list, or NULL
  //if list is empty.
public:
  //Default Constructor. Will properly initialize a list to
  //be an empty list, to which values can be added.
  SortedListClass(
  );
  //Copy constructor. Will make a complete (deep) copy of the list, such
  //that one can be changed without affecting the other.
  SortedListClass(
    const SortedListClass<T>& rhs
  );
  //Destructor. Responsible for making sure any dynamic memory
  //associated with an object is freed up when the object is
  //being destroyed.
  ~SortedListClass(
  );
  //Clears the list to an empty state without resulting in any
  //memory leaks.
  void clear(
  );
  //Allows the user to insert a value into the list. Since this
  //is a sorted list, there is no need to specify where in the list
  //to insert the element. It will insert it in the appropriate
  //location based on the value being inserted. If the node value
  //being inserted is found to be "equal to" one or more node values
  //already in the list, the newly inserted node will be placed AFTER
  //the previously inserted nodes. The fact that duplicates are placed
  //AFTER the nodes with the same value may not seem important right
  //now, but make sure you implement it this way, because it may be
  //important later!
  void insertValue(
    const T& valToInsert //The value to insert into the list
  );
  //Prints the contents of the list from head to tail to the screen.
  //Begins with a line reading "Forward List Contents Follow:", then
  //prints one list element per line, each indented two spaces, then prints
  //the line "End Of List Contents" to indicate the end of the list.
  void printForward(
  ) const;
  //Prints the contents of the list from tail to head to the screen.
  //Begins with a line reading "Backward List Contents Follow:", then
  //prints one list element per line, each indented two spaces, then prints
  //the line "End Of List Contents" to indicate the end of the list.
  void printBackward(
  ) const;
  //Removes the front item from the list and returns the value that
  //was contained in it via the reference parameter. If the list
  //was empty, the function returns false to indicate failure, and
  //the contents of the reference parameter upon return is undefined
  //(meaning the value of the param named theVal may be the same as
  //it was provided, or it may be changed to any arbitrary value).
  //If the list was not empty and the first item was successfully
  //removed, true is returned, and the reference parameter will
  //be set to the item that was removed.
  bool removeFront(
    T& theVal
  );
  //Removes the last item from the list and returns the value that
  //was contained in it via the reference parameter. If the list
  //was empty, the function returns false to indicate failure, and
  //the contents of the reference parameter upon return is undefined.
  //If the list was not empty and the last item was successfully
  //removed, true is returned, and the reference parameter will
  //be set to the item that was removed.
  bool removeLast(
    T& theVal
  );
  //Returns the number of nodes contained in the list.
  int getNumElems(
  ) const;
  //Provides the value stored in the node at index provided in the
  //0-based "index" parameter. If the index is out of range, then outVal
  //remains unchanged and false is returned. Otherwise, the function
  //returns true, and the reference parameter outVal will contain
  //a copy of the value at that location.
  bool getElemAtIndex(
    const int index,
    T& outVal
  ) const;
};

#include "SortedListClass.inl"
#endif