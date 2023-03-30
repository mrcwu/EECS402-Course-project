#include "PatternClass.h"

#include <fstream>
#include <string>
#include "constants.h"

#include <iostream>
using namespace std;

// constructor
PatternClass::PatternClass(int inRow, int inCol, int inColorNum) 
{
  createHollowRectangle(inRow, inCol, inColorNum);
}

PatternClass::PatternClass(string fileName, int inColorNum) 
{
  readPattern(fileName, inColorNum);
}

// destructor: delete the dynamic allocation matrix to prevent memory leak
PatternClass::~PatternClass() 
{
  for (int i = 0; i < patRow; ++i) 
  {
    delete[] patMatrix[i];
  }
  delete[] patMatrix;
}


// create the matrix function by dynamic allocation
void PatternClass::createMatrix(int inRow, int inCol) 
{
  patMatrix = new int * [inRow];
  for (int i = 0; i < inRow; ++i)
  {
    patMatrix[i] = new int[inCol];
  }
}


// get functions: return the row, col, pattern color, or has pixel or not
int PatternClass::getRow() 
{
  return patRow;
}

int PatternClass::getCol() 
{
  return patCol;
}

int PatternClass::getColor() 
{
  return patColor;
}

int PatternClass::getPixelAtLocation(int inRowIndex, int inColIndex) 
{
  return patMatrix[inRowIndex][inColIndex];
}


// functions to create a pattern
// create a pattern by input filename and inColorNum
void PatternClass::readPattern(string fileName, int inColorNum) 
{
  ifstream inFile;

  patColor = inColorNum;

  // 1. open the file
  inFile.open(fileName.c_str());
  // 2. the first row have 2 numbers row and col, 
  // stored them into local variables
  inFile >> patCol; // Correction: this num was falsely assigned to patRow
  inFile >> patRow; // Correction: this num was falsely assigned to patCol

  // 3. create the matrix to store colorclass
  createMatrix(patRow, patCol);

  // 4. Read color to the matrix
  for (int i = 0; i < patRow; ++i)
  {
    for (int j = 0; j < patCol; ++j)
    {
      inFile >> patMatrix[i][j];
    }
  }
}

// create a hollow rectangle pattern by input row, col, and color number
void PatternClass::createHollowRectangle(int inRow, int inCol, int inColorNum)
{
  patRow = inRow;
  patCol = inCol;
  patColor = inColorNum;
  int firstRowIndex = 0;
  int lastRowIndex = patRow - 1;
  int firstColIndex = 0;
  int lastColIndex = patCol - 1;

  // 1. create the matrix
  createMatrix(patRow, patCol);

  // 2. fill in the pixel information, since the rectangle is hollow,
  // only the four sides has pixel
  for (int i = 0; i < patRow; ++i)
  {
    for (int j = 0; j < patCol; ++j)
    {
      if ((i == firstRowIndex) || (i == lastRowIndex) ||
          (j == firstColIndex) || (j == lastColIndex)) 
          {
            patMatrix[i][j] = HAS_PIXEL;
          }
      else 
      {
        patMatrix[i][j] = NO_PIXEL;
      }
    }
  }

}

