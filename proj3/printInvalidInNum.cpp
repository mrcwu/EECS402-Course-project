#include <iostream>
#include "printInvalidInNum.h"
using namespace std;

void printInvalidInNum(bool isInvalid) 
{
  if (isInvalid)
  {
    cout << "ERROR: the input is invalid. Please try again." << endl;
  }
}