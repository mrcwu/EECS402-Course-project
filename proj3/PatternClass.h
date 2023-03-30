#ifndef _PATTERNCLASS_H_
#define _PATTERNCLASS_H_
#include <fstream>
#include <string>

#include <iostream>
using namespace std;


// this is a class to specify a pattern.
class PatternClass
{
  private:
    int** patMatrix;
    int patRow;
    int patCol;
    int patColor;

    void createMatrix(int inRow, int inCol);

  public:
    // constructor
    PatternClass(int inRow, int inCol, int inColorNum);
    PatternClass(string fileName, int inColorNum);
    // destructor
    ~PatternClass();

    // functions to get row, col, pattern color
    int getRow();
    int getCol();
    int getColor();
    int getPixelAtLocation(int inRowIndex, int inColIndex);

    // functions to create a pattern
    void readPattern(string fileName, int inColorNum); // import from a file
    void createHollowRectangle(int inRow, int inCol, int inColorNum);
    

};

#endif
