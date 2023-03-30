#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "LIFOStackClass.h"

#include <iostream>
using namespace std;

// Programmer: Conan Wu
// Date: November 22, 2022
// Project 4
// Purpose: 
// 1. build up a base class "LinkedNodeClass" for each node
// 2. build up a higher class "SortedListClass.h" for node lists 
// 3. build up FIFO and LIFO data structure class base on "LinkedNodeClass"
// All of the classes are the foundation for project 5


//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 

int main()
{
  //This is just a placeholder main function - it does exceptionally
  //little actual testing, so you'll want to add your own tests here.
  //Feel free to leave your tests in the version of this file you
  //submit, but we will not be running your main function, so the
  //output, etc., of your main doesn't need to match anything from
  //a sample output, etc.
  SortedListClass testList;
  
  testList.printForward();
  testList.insertValue(42);
  testList.printForward();
  
  return 0;
}

#endif