#include "ColorImageClass.h"

#include "ColorClass.h"
#include "PatternClass.h"
#include "constants.h"

#include <fstream>
#include <string>

#include <iostream>
using namespace std;

// ColorImageClass

// constructor
// create the colorimageclass according to the given row and col in constructor 
ColorImageClass::ColorImageClass(int inRow, int inCol, int inColorNum) 
{
  createFilledRectangle(inRow, inCol, inColorNum);
}

// create the colorimageclass according to the image file in constructor
ColorImageClass::ColorImageClass(string fileName) 
{
  readImage(fileName);
}

// destructor: delete the dynamic allocation matrix to prevent memory leak
ColorImageClass::~ColorImageClass() 
{
  for (int i = 0; i < imgRow; ++i) 
  {
    delete[] imgMatrix[i];
  }
  delete[] imgMatrix;
}

// checking function: check whether the input class of row and col are valid
// Input: starting Index of Rows and Columns, inserted picture's row and col
// Output: bool (true if the location is valid)
bool ColorImageClass::isValidLoc(int startRowIndex, 
                                 int startColIndex, 
                                 int inRow, 
                                 int inCol) 
{
  int endRowIndex = startRowIndex + inRow;
  int endColIndex = startColIndex + inCol;

  return (endRowIndex < imgRow &&
          startRowIndex >= 0 && // the array index cannot be "< 0"
          endColIndex < imgCol &&
          startColIndex >= 0);
}


// createMatrix using dynamic allocation
void ColorImageClass::createMatrix(int inRow, int inCol) 
{
  imgMatrix = new ColorClass * [inRow];
  for (int i = 0; i < inRow; ++i)
  {
    imgMatrix[i] = new ColorClass[inCol];
  }

}

// this function will return the row number
int ColorImageClass::getRow()
{
  return imgRow;
}
// this function will return the col number
int ColorImageClass::getCol()
{
  return imgCol;
}
// this function will return the max image color number
int ColorImageClass::getMaxColor()
{
  return imgMaxColor;
}


// this function read the ppm file with a file name. Note that this function 
// DOESN'T check the file itself is correct or not
// Input: a string of file name to read from
void ColorImageClass::readImage(string fileName)
{
    ifstream inFile;
    string inMagicNum;

    // 1. open the file
    inFile.open(fileName.c_str());
    // 2. the first 3 rows have 4 numbers, stored them into local variables
    inFile >> inMagicNum;
    inFile >> imgCol; // Correction: this num was falsely assigned to imgRow
    inFile >> imgRow; // Correction: this num was falsely assigned to imgCol
    inFile >> imgMaxColor;

    // 3. create the matrix to store colorclass
    createMatrix(imgRow, imgCol);

    // 4. Read color to the matrix
    for (int i = 0; i < imgRow; ++i)
    {
      for (int j = 0; j < imgCol; ++j)
      {
        imgMatrix[i][j].readColor(inFile);
      }
    }

}

// Export function. export current color image class into a file
// Input: a string of file name to export to
void ColorImageClass::writeImage(ofstream& outFile) 
{
  int lastColIndex = imgCol - 1;
  outFile << MAGIC_NUMBER << "\n";
  outFile << imgCol << " " << imgRow << "\n";
  outFile << imgMaxColor << "\n";
  for (int i = 0; i < imgRow; ++i)
  {
    for (int j = 0; j < imgCol; ++j)
    {
      imgMatrix[i][j].writeColor(outFile);
      if (j != lastColIndex)
      {
        outFile << ' ';
      }
    }
    outFile << '\n';
  }
}

// This is a function to create a filled rectangle ppm image
void ColorImageClass::createFilledRectangle(int inRow, 
                                            int inCol, 
                                            int inColorNum) 
{
  imgRow = inRow;
  imgCol = inCol;

  // 1. create a matrix to store colorclass
  createMatrix(imgRow, imgCol);

  // 2. fill in the color into each color class
  for (int i = 0; i < imgRow; ++i)
  {
    for (int j = 0; j < imgCol; ++j)
    {
      if (inColorNum == RED) 
      {
        imgMatrix[i][j].setToRed();
      }
      else if (inColorNum == GREEN) 
      {
        imgMatrix[i][j].setToGreen();
      }
      else if (inColorNum == BLUE) 
      {
        imgMatrix[i][j].setToBlue();
      }
      else if (inColorNum == BLACK) 
      {
        imgMatrix[i][j].setToBlack();
      }
      else if (inColorNum == WHITE) 
      {
        imgMatrix[i][j].setToWhite();
      }

    }
  }
}

// This function will insert the image inImg from a color image class at 
// a specific location "startRowIndex, startColIndex"
// Input: 
// 1. a colorimgclass to insert into current base ppm
// 2. the starting points of upper left row and col
// 3. the transparent color specified by users
void ColorImageClass::insertImageFrom(ColorImageClass& inImg, 
                                      int const startRowIndex, 
                                      int const startColIndex,
                                      int const transColor)
{
  int inRow = inImg.getRow();
  int inCol = inImg.getCol();
  
  // 2. initialize a tempColor to store each pixel from the image 
  // which is going to insert in.
  ColorClass tempColor;
  int tempRed;
  int tempGreen;
  int tempBlue;

  // 3. check if is in the right location
  if (isValidLoc(startRowIndex, startColIndex, inRow, inCol)) 
  {
    for (int i = 0; i < inRow; ++i)
    {
      for (int j = 0; j < inCol; ++j)
      {
        // write the pixel information into tempColor
        inImg.getColorAtLocation(i, j, tempColor);
        // get the RGB number from tempColor
        tempRed = tempColor.getRed();
        tempGreen = tempColor.getGreen();
        tempBlue = tempColor.getBlue();

        // 3. consider the transparent color, if current pixel is 
        // the transparent color, it will skip it
        if (transColor == NOCOLOR) 
        {
          setColorAtLocation(startRowIndex + i, startColIndex + j, tempColor);
        }
        else if (transColor == RED) 
        {
          if (!((tempRed == MAX_COLOR_VALUE) && 
                (tempGreen == MIN_COLOR_VALUE) &&
                (tempBlue == MIN_COLOR_VALUE))) 
          {
            setColorAtLocation(startRowIndex + i, startColIndex + j, tempColor);
          }
        }
        else if (transColor == GREEN) 
        {
          if (!((tempRed == MIN_COLOR_VALUE) && 
                (tempGreen == MAX_COLOR_VALUE) &&
                (tempBlue == MIN_COLOR_VALUE))) 
          {
            setColorAtLocation(startRowIndex + i, startColIndex + j, tempColor);
          }
        }
        else if (transColor == BLUE) 
        {
          if (!((tempRed == MIN_COLOR_VALUE) && 
                (tempGreen == MIN_COLOR_VALUE) &&
                (tempBlue == MAX_COLOR_VALUE))) 
          {
            setColorAtLocation(startRowIndex + i, startColIndex + j, tempColor);
          }
        }
        else if (transColor == BLACK) 
        {
          if (!((tempRed == MIN_COLOR_VALUE) && 
                (tempGreen == MIN_COLOR_VALUE) &&
                (tempBlue == MIN_COLOR_VALUE))) 
          {
            setColorAtLocation(startRowIndex + i, startColIndex + j, tempColor);
          }
        }
        else if (transColor == WHITE) 
        {
          if (!((tempRed == MAX_COLOR_VALUE) && 
                (tempGreen == MAX_COLOR_VALUE) &&
                (tempBlue == MAX_COLOR_VALUE))) 
          {
            setColorAtLocation(startRowIndex + i, startColIndex + j, tempColor);
          }
        }

      }
    }

  }

}

// this function will insert the pattern to the current colorImageClass
// Input: 
// 1. a patternclass to insert into current base ppm
// 2. the starting points of upper left row and col
void ColorImageClass::insertPatternFrom(PatternClass& inPat,
                                        int const startRowIndex, 
                                        int const startColIndex) 
{
  int inRow = inPat.getRow();
  int inCol = inPat.getCol();
  int inColorNum = inPat.getColor();

  if (isValidLoc(startRowIndex, startColIndex, inRow, inCol)) 
  {
    // determine the color
    ColorClass tempColor;
    if (inColorNum == RED) 
    {
      tempColor.setToRed();
    }
    else if (inColorNum == GREEN) 
    {
      tempColor.setToGreen();
    }
    else if (inColorNum == BLUE) 
    {
      tempColor.setToBlue();
    }
    else if (inColorNum == BLACK) 
    {
      tempColor.setToBlack();
    }
    else if (inColorNum == WHITE) 
    {
      tempColor.setToWhite();
    }

    int pixelIndicator;

    for (int i = 0; i < inRow; ++i)
    {
      for (int j = 0; j < inCol; ++j)
      {
        
        pixelIndicator = inPat.getPixelAtLocation(i, j);
        if (pixelIndicator == HAS_PIXEL) 
        {
          setColorAtLocation(startRowIndex + i, startColIndex + j, tempColor);
        }
      }
    }
  }


}



// This function attempts to set the pixel at the location specified by the
//  inRowIndex, inColIndex parameters to the color specified via the 
// “inColor” parameter.
// Input: two Int inRowIndex, inColIndex, 
// a ColorClass (inColor, the color infomation)
void ColorImageClass::setColorAtLocation(int inRowIndex, 
                                         int inColIndex,
                                         ColorClass &inColor) 
{
  imgMatrix[inRowIndex][inColIndex].setTo(inColor);
}


// If the row/column provided is a valid row/column for the image, 
// this function returns true and the output parameter "outColor" is 
// assigned to the color of the image pixel at that location.
// Input: RowColumnClass (info of color location), 
// ColorClass (info of color)
void ColorImageClass::getColorAtLocation(int inRowIndex, 
                                         int inColIndex,
                                         ColorClass &outColor) 
{
  outColor.setTo(imgMatrix[inRowIndex][inColIndex]);

}
