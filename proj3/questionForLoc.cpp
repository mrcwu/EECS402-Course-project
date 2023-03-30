#include "questionForLoc.h"

#include <fstream>
#include <string>
#include "printInvalidInNum.h"
#include "ColorImageClass.h"
#include "constants.h"

#include <iostream>
using namespace std;


// this is a function for asking the users what locations they want to insert
// Input: 
// 1. the starting point row and col indexes, 
// 2. the full sizes in row and col of the object that user want to insert, 
// 3. the current base ppm image, 
// 4. a int to specify the question type, it will effect the cout 
// messages of questions.
void questionForLoc(int& startRowIndex, int& startColIndex,
                    int& fullNumRow, int& fullNumCol,
                    ColorImageClass& baseImg, 
                    int const questionType) 
{
  do 
  {
    if (cin.fail())
      {
        cin.clear();
        cin.ignore(MAX_CHAR_IN_CIN, '\n');
      }

    // already have file to put
    if ((questionType == SPECIFY_UL_ONLY_PAT) || 
        (questionType == SPECIFY_UL_ONLY_IMG))
    {
      if (questionType == SPECIFY_UL_ONLY_PAT)
      {
        cout << "Enter upper left corner of pattern row and column: ";
      }

      else if (questionType == SPECIFY_UL_ONLY_IMG)
      {
        cout << "Enter upper left corner to insert image row and column: ";
      }

      cin >> startRowIndex;
      cin >> startColIndex;

    }

    // no file
    // Choose the specify the upper left and lower right location
    // for rectangle
    else if (questionType == SPECIFY_UL_LR) 
    {
      // variables for the first question extend
      int lowRightRow;
      int lowRightCol;

      cout << "Enter upper left corner row and column: ";
      cin >> startRowIndex;
      cin >> startColIndex;

      cout << "Enter lower right corner row and column: ";
      cin >> lowRightRow;
      cin >> lowRightCol;

      // calculation
      fullNumRow = lowRightRow - startRowIndex;
      fullNumCol = lowRightCol - startColIndex;
    }

    // Choose the specify the upper left and dimention
    // for rectangle
    else if (questionType == SPECIFY_UL_AND_DIMENTION) 
    {
      // variables for the first question extend
      int numRow;
      int numCol;

      cout << "Enter upper left corner row and column: ";
      cin >> startRowIndex;
      cin >> startColIndex;

      cout << "Enter int for number of rows: ";
      cin >> numRow;

      cout << "Enter int for number of columns: ";
      cin >> numCol;


      // calculation
      fullNumRow = numRow;
      fullNumCol = numCol;
    }

    // Choose the specify the center for rectangle
    else if (questionType == SPECIFY_EXT_FROM_CENTER) 
    {
      // variables for the first question extend
      int cenRow;
      int cenCol;
      int halfNumRow;
      int halfNumCol;
    
      cout << "Enter rectangle center row and column: ";
      cin >> cenRow;
      cin >> cenCol;

      cout << "Enter int for half number of rows: ";
      cin >> halfNumRow;

      cout << "Enter int for half number of columns: ";
      cin >> halfNumCol;

      // calculation
      startRowIndex = cenRow - halfNumRow;
      startColIndex = cenCol - halfNumCol;
      fullNumRow = halfNumRow * 2;
      fullNumCol = halfNumCol * 2;
    }

    // if the input is invalid, it will show error message
    printInvalidInNum(!(baseImg.isValidLoc(startRowIndex, startColIndex, 
                                           fullNumRow, fullNumCol)) || 
                                           cin.fail());

  }
  
  while (!(baseImg.isValidLoc(startRowIndex, startColIndex, 
                              fullNumRow, fullNumCol)) || 
                              cin.fail());

}