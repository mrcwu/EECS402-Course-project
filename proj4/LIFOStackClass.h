#ifndef _LIFOSTACK_CLASS_H_
#define _LIFOSTACK_CLASS_H_

#include "LinkedNodeClass.h"

class LIFOStackClass
{
private:
  LinkedNodeClass *head; //Points to the first node in a stack, or NULL
  //if stack is empty.
  LinkedNodeClass *tail; //Points to the last node in a stack, or NULL
  //if stack is empty.
public:
  //Default Constructor. Will properly initialize a stack to
  //be an empty stack, to which values can be added.
  LIFOStackClass(
  );
  //Destructor. Responsible for making sure any dynamic memory
  //associated with an object is freed up when the object is
  //being destroyed.
  ~LIFOStackClass(
  );
  //Inserts the value provided (newItem) into the stack.
  void push(
            const int &newItem
            );
  //Attempts to take the next item out of the stack. If the
  //stack is empty, the function returns false and the state
  //of the reference parameter (outItem) is undefined. If the
  //stack is not empty, the function returns true and outItem
  //becomes a copy of the next item in the stack, which is
  //removed from the data structure.
  bool pop(
           int &outItem
           );
  //Prints out the contents of the stack. All printing is done
  //on one line, using a single space to separate values, and a
  //single newline character is printed at the end.
  void print(
  ) const;
  //Returns the number of nodes contained in the stack.
  int getNumElems(
  ) const;
  //Clears the stack to an empty state without resulting in any
  //memory leaks.
  void clear(
  );
};

#endif