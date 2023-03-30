#include <iostream>

using namespace std;

// Programmer: Conan Wu
// Date: October 6, 2022
// Purpose: Project 2 - 3 classes to represent and utilize colors and images


// GLOBAL CONSTANT DECLARING
// I: for ColorClass
const int MAX_COLOR_VALUE = 1000;
const int MIN_COLOR_VALUE = 0;
// II: for RowColumnClass
const int DEFAULT_ROW_COL_VALUE = -99999;
// III: for ColorImageClass
const int ROW_LIMIT = 10;
const int COL_LIMIT = 18;

// CLASS DEFINITION (ONLY PROTOTYPES)

// This class contain the information describing a color and several methods
//  to change the color in the object of this class.
class ColorClass 
{
  private:
    // declare the local values
    int redVal;
    int greenVal;
    int blueVal;

    // custom funtion
    int clipInRange(int inVal);
    bool shouldClip(int inVal);

  public:
    // constructor
    ColorClass();
    ColorClass(int inRed,int inGreen,int inBlue);

    // required functions
    void setToBlack();
    void setToRed();
    void setToGreen();
    void setToBlue();
    void setToWhite();

    bool setTo(int inRed, int inGreen, int inBlue);
    bool setTo(ColorClass &inColor);
    bool addColor(ColorClass &rhs);
    bool subtractColor(ColorClass &rhs);
    bool adjustBrightness(double adjFactor);
    void printComponentValues();

};

// this class is just containing a location of a row number and a col number 
// for a specific pixel.
class RowColumnClass 
{
  private:
    // setup local variables
    int rowVal;
    int colVal;

  public:
    // constructor
    RowColumnClass();
    RowColumnClass(int inRow, int inCol);
    // the required functions
    void setRowCol(int inRow, int inCol);
    void setRow (int inRow);
    void setCol(int inCol);
    int getRow();
    int getCol(); 
    void addRowColTo(RowColumnClass &inRowCol);
    void printRowCol();

};


// this is a class to represent a image. There are some methods contained
// inside to adjust and set the image.
class ColorImageClass 
{
  private:
    // declare the local values;
    ColorClass imgMatrix[ROW_LIMIT][COL_LIMIT];

    // custom function
    bool isValidLoc(RowColumnClass &inRowCol);

  public:
    // constructor
    ColorImageClass();
    // the required functions
    void initializeTo(ColorClass &inColor);
    bool addImageTo(ColorImageClass &rhsImg);
    bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd []);
    bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);
    bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);
    void printImage();

};


#ifdef ANDREW_TEST
#include "andrewTest.h"
#else


// MAIN FUNCTION
int main() 
{
  return 0;
}


#endif


// CLASS METHOD DEFINITION

// I: for ColorClass

// custom funtion 1: check whether the input color value 
// is in the correct range or not. If it's not, the function will clip it.
// Input: the color value
// Output: the adjusted color value
int ColorClass::clipInRange(int inVal) 
{
  if (inVal > MAX_COLOR_VALUE) 
  {
    return MAX_COLOR_VALUE;
  } 
  else if (inVal < MIN_COLOR_VALUE) 
  {
    return MIN_COLOR_VALUE;
  }
  else 
  {
    return inVal;
  }
  
}

// custom function 2: check whether the input color value should be clipped.
// Input: the color value
// output: bool (true means the number is out of range)
bool ColorClass::shouldClip(int inVal) 
{
  if ((inVal > MAX_COLOR_VALUE) && (inVal < MIN_COLOR_VALUE))
  {
    return false;
  } 
  else 
  {
    return true;
  }
}

// set the default value to constructor.
ColorClass::ColorClass() 
{
  redVal = MAX_COLOR_VALUE;
  greenVal = MAX_COLOR_VALUE;
  blueVal = MAX_COLOR_VALUE;
}

// If the users want custom value, they can set the numbers to the constructor.
// Input: color values
ColorClass::ColorClass(int inRed,int inGreen,int inBlue) 
{
  redVal = clipInRange(inRed);
  greenVal = clipInRange(inGreen);
  blueVal = clipInRange(inBlue);
}

// required functions
// this function set the color to black
void ColorClass::setToBlack() 
{
  redVal = MIN_COLOR_VALUE;
  greenVal = MIN_COLOR_VALUE;
  blueVal = MIN_COLOR_VALUE;
}

// this function set the color to red
void ColorClass::setToRed() 
{
  redVal = MAX_COLOR_VALUE;
  greenVal = MIN_COLOR_VALUE;
  blueVal = MIN_COLOR_VALUE;
}

// this function set the color to green
void ColorClass::setToGreen() 
{
  redVal = MIN_COLOR_VALUE;
  greenVal = MAX_COLOR_VALUE;
  blueVal = MIN_COLOR_VALUE;
}

// this function set the color to blue
void ColorClass::setToBlue() 
{
  redVal = MIN_COLOR_VALUE;
  greenVal = MIN_COLOR_VALUE;
  blueVal = MAX_COLOR_VALUE;
}

// this function set the color to white
void ColorClass::setToWhite() 
{
  redVal = MAX_COLOR_VALUE;
  greenVal = MAX_COLOR_VALUE;
  blueVal = MAX_COLOR_VALUE;
}

// This function sets the color object's RGB values to the provided values. 
// If any input value is outside the allowed color value range, 
// then the assigned value is "clipped" in order to keep the RGB color 
// values within the valid range.
// Input: color values
// Output: bool (true means one of the input values is out of range and 
// should be clipped)
bool ColorClass::setTo(int inRed, int inGreen, int inBlue) 
{
  redVal = clipInRange(inRed);
  greenVal = clipInRange(inGreen);
  blueVal = clipInRange(inBlue);

  return (shouldClip(inRed) || shouldClip(inGreen) || shouldClip(inBlue));
  
}

// This function sets the color's component color values to the same as 
// those in the "inColor" input parameter.
// Input: a ColorClass
// Output: bool (true means one of the color values in the input class is 
// out of range and should be clipped)
bool ColorClass::setTo(ColorClass &inColor) 
{
  redVal = inColor.redVal;
  greenVal = inColor.greenVal;
  blueVal = inColor.blueVal;

  return (shouldClip(redVal) || shouldClip(greenVal) || 
          shouldClip(blueVal));
}

// This function causes each RGB value to have the corresponding value from 
// the input parameter color added to it.
// Input: the ColorClass to be added with
// Output: bool (true means one of the color values after adding is 
// out of range and should be clipped)
bool ColorClass::addColor(ColorClass &rhs) 
{
  int tempRedVal = redVal + rhs.redVal;
  int tempGreenVal = greenVal + rhs.greenVal;
  int tempBlueVal = blueVal + rhs.blueVal;

  redVal = clipInRange(tempRedVal);
  greenVal = clipInRange(tempGreenVal);
  blueVal = clipInRange(tempBlueVal);

  return (shouldClip(tempRedVal) || shouldClip(tempGreenVal) || 
          shouldClip(tempBlueVal));

}

// This function causes each RGB value to have the corresponding value from
//  the input parameter subtracted from it.
// Input: the ColorClass to be substracted with
// Output: bool (true means one of the color values after subtracting is 
// out of range and should be clipped)
bool ColorClass::subtractColor(ColorClass &rhs) 
{
  int tempRedVal = redVal - rhs.redVal;
  int tempGreenVal = greenVal - rhs.greenVal;
  int tempBlueVal = blueVal - rhs.blueVal;

  redVal = clipInRange(tempRedVal);
  greenVal = clipInRange(tempGreenVal);
  blueVal = clipInRange(tempBlueVal);

  return (shouldClip(tempRedVal) || shouldClip(tempGreenVal) || 
          shouldClip(tempBlueVal));
}


// This function performs a simplified brightness adjustment, 
// which multiplies each RGB value by the adjustment factor provided.
// Input: a double (the adjust factor. If adjFactor is greater than 1, 
// the color gets brighter, if adjFactor is less than 1, 
// the color gets dimmer.
// Output: bool (true means one of the color values after adjusting is 
// out of range and should be clipped)
bool ColorClass::adjustBrightness(double adjFactor) 
{
  int tempRedVal = int(redVal * adjFactor);
  int tempGreenVal = int(greenVal * adjFactor);
  int tempBlueVal = int(blueVal * adjFactor);

  redVal = clipInRange(tempRedVal);
  greenVal = clipInRange(tempGreenVal);
  blueVal = clipInRange(tempBlueVal);

  return (shouldClip(tempRedVal) || shouldClip(tempGreenVal) || 
          shouldClip(tempBlueVal));
}

// Prints the component color values to the console 
// using the following format: "R: <red> G: <green> B: <blue>"
void ColorClass::printComponentValues() 
{
  cout << "R: " << redVal << " G: " << greenVal << " B: " << blueVal;
}


// II: for RowColumnClass

// setup default to the variables in the constructor
RowColumnClass::RowColumnClass() 
{
  rowVal = DEFAULT_ROW_COL_VALUE;
  colVal = DEFAULT_ROW_COL_VALUE;
}

// set the local variables to the custom input numbers in the constructor
RowColumnClass::RowColumnClass(int inRow, int inCol) 
{
  rowVal = inRow;
  colVal = inCol;
}

// set the local variables to the custom input numbers
// Input: two ints (Row and Col numbers)
void RowColumnClass::setRowCol(int inRow, int inCol) 
{
  rowVal = inRow;
  colVal = inCol;
}

// set the local variable rowVal to the custom input number
// Input: an int (Row number)
void RowColumnClass::setRow (int inRow) 
{
  rowVal = inRow;
}

// set the local variable colVal to the custom input number
// Input: an int (Col number)
void RowColumnClass::setCol(int inCol) 
{
  colVal = inCol;
}

// return the local variable rowVal
int RowColumnClass::getRow() 
{
  return rowVal;
}

// return the local variable colVal
int RowColumnClass::getCol() 
{
  return colVal;
}

// This function adds the row and column index values in the input parameter 
// to the row and column index of the object the function is called on.
void RowColumnClass::addRowColTo(RowColumnClass &inRowCol) 
{
  rowVal += inRowCol.rowVal;
  colVal += inRowCol.colVal;
}

// This function prints this object's attributes in the format 
// "[<row>,<col>]"
void RowColumnClass::printRowCol() 
{
  cout << "[" << rowVal << "," << colVal << "]";
}


// III: for ColorImageClass

// custom function: check whether the input class of row and col are valid
// Input: RowColumnClass (the infomation of the color location)
// Output: bool (true if the location is valid)
bool ColorImageClass::isValidLoc(RowColumnClass &inRowCol) 
{
  return (inRowCol.getRow() < ROW_LIMIT &&
          inRowCol.getRow() >= 0 && // the array index cannot be "< 0"
          inRowCol.getCol() < COL_LIMIT &&
          inRowCol.getCol() >= 0);
}

// set all of the pixel's default value to black with constructor 
ColorImageClass::ColorImageClass() 
{
  for (int row = 0; row < ROW_LIMIT; row++) 
  {
    for (int col = 0; col < COL_LIMIT; col++) 
    {
      imgMatrix[row][col].setToBlack();
    }
  }
}

// This function initializes all image pixels to the color provided 
// via the input parameter.
// Input: a ColorClass
void ColorImageClass::initializeTo(ColorClass &inColor) 
{
  for (int row = 0; row < ROW_LIMIT; row++) 
  {
    for (int col = 0; col < COL_LIMIT; col++) 
    {
      imgMatrix[row][col].setTo(inColor);
    }
  }
}

// This function performs a pixel-wise addition, 
// such that each pixel in the image has the pixel in the corresponding 
// location in the right-hand side input image added to it.
// input: a ColorImageClass to be added with
// output: bool (true if the result of one or more of the pixel additions 
// required color value clipping)
bool ColorImageClass::addImageTo(ColorImageClass &rhsImg) 
{
  bool isClipped = false;

  for (int row = 0; row < ROW_LIMIT; row++) 
  {
    for (int col = 0; col < COL_LIMIT; col++) 
    {
      isClipped += imgMatrix[row][col].addColor(rhsImg.imgMatrix[row][col]);
    }
  }

  return isClipped;
}

// This function causes the image's pixel values to be set to the sum of the
//  corresponding pixels in each image in the imagesToAdd input parameter.
// input: an int (numImgsToAdd, length of the following array), 
// an array of ColorImageClass (imagesToAdd) 
// output: bool (true if one or more of the pixel additions is clipping)
bool ColorImageClass::addImages(int numImgsToAdd, 
                                ColorImageClass imagesToAdd []) 
{
  bool isClipped = false;

  // put the current image pixel to be blank (black color)
  ColorClass blankColor;
  blankColor.setToBlack();
  initializeTo(blankColor);

  for (int imgIndex = 0; imgIndex < numImgsToAdd; imgIndex++) 
  {
    isClipped += addImageTo(imagesToAdd[imgIndex]);
  }

  return isClipped;
}

// This function attempts to set the pixel at the location specified by the
//  “inRowCol” parameter to the color specified via the “inColor” parameter.
// Input: a RowColumnClass (inRowCol, location of row and col), 
// a ColorClass (inColor, the color infomation)
// Output: bool (true if the location (RowColumnClass) 
// is correctly specified);
bool ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol, 
                                         ColorClass &inColor) 
{
  if (isValidLoc(inRowCol))
      {
        imgMatrix[inRowCol.getRow()][inRowCol.getCol()].setTo(inColor);

        return true;
      } 
  else 
  {
    return false;
  }
    
}

// If the row/column provided is a valid row/column for the image, 
// this function returns true and the output parameter "outColor" is 
// assigned to the color of the image pixel at that location.
// Input: RowColumnClass (info of color location), 
// ColorClass (info of color)
// Output: bool (true if the location (RowColumnClass) 
// is correctly specified)
bool ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol, 
                                         ColorClass &outColor) 
{
  if (isValidLoc(inRowCol)) 
  {
    outColor.setTo(imgMatrix[inRowCol.getRow()][inRowCol.getCol()]);

    return true;
  }
  else 
  {
    return false;
  }
}

// This function prints the contents of the image to the screen.
void ColorImageClass::printImage() 
{
  int lastColIndex = COL_LIMIT - 1; // the index number of the last column
  
  for (int row = 0; row < ROW_LIMIT; row++) 
  {
    for (int col = 0; col < COL_LIMIT; col++) 
    {
      imgMatrix[row][col].printComponentValues();

      if (col == lastColIndex) 
      {
        cout << endl; // image is printed one row of pixels per line
      }
      else 
      {
        cout << "--"; // Between each pixel in a row, two dashes are printed
        //  in order to separate the values
      }
    }
  }
}