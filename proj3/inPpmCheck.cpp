#include "inPpmCheck.h"

#include <fstream>
#include <string>

#include "constants.h"

#include <iostream>
using namespace std;

//  this function will give a bool after checking the parameter in a ppm file,
// if the parameter is correct, it will return true.
// Input: a string of file name
// Output: bool, true means the file can be read
bool inPpmCheck (string const fileName)
{
  ifstream inFile;
  string inMagicNum;
  int inRow;
  int inCol;
  int inMaxColor;

  inFile.open(fileName.c_str());

  inFile >> inMagicNum;
  inFile >> inRow;
  inFile >> inCol;
  inFile >> inMaxColor;

  if (
      (!inFile.fail()) && 
      (inMagicNum == MAGIC_NUMBER) && 
      (inMaxColor == MAX_COLOR_VALUE) &&
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
