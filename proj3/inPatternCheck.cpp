#include "inPatternCheck.h"

#include <fstream>
#include <string>

#include <iostream>
using namespace std;

//  this function will give a bool after checking the parameter in a pattern 
// file, if the parameter is correct, it will return true.
// Input: a string of file name
// Output: bool, true means the file can be read
bool inPatternCheck(string const fileName)
{
  ifstream inFile;
  int inRow;
  int inCol;

  inFile.open(fileName.c_str());
  inFile >> inRow;
  inFile >> inCol;


  if (
      (!inFile.fail()) && 
      (inRow > 0) && 
      (inCol > 0) && 
      (!inFile.eof())
    )
  {
    return true;
  }
  else
  {
    return false;
  }

}
