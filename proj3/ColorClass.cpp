#include "ColorClass.h"

#include "constants.h"
#include <fstream>
#include <iostream>
using namespace std;

// ColorClass

// clip checking funtion: check whether the input color value 
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


// this funtion will read the color and put the color into the current pixel
// Input: the stream data, usually the color number information take from a file
void ColorClass::readColor(ifstream &inFile) 
{
  // read each color
  int colorList[RGB_LENGTH];
  for (int i = 0; i < RGB_LENGTH; i++) 
  {
    inFile >> colorList[i];
  }

  // put the color into the current pixel
  redVal = colorList[RED_IND];
  greenVal = colorList[GREEN_IND];
  blueVal = colorList[BLUE_IND];

}


// this funtion will export the current pixel
void ColorClass::writeColor(ofstream &outFile) 
{
  outFile << redVal << ' ' << greenVal << ' ' << blueVal;
}

// these functions return the color values
int ColorClass::getRed()
{
    return redVal;
}

int ColorClass::getGreen()
{
    return greenVal;
}

int ColorClass::getBlue()
{
    return blueVal;
}


// This function sets the color object's RGB values to the provided values. 
// If any input value is outside the allowed color value range, 
// then the assigned value is "clipped" in order to keep the RGB color 
// values within the valid range.
// Input: color values
void ColorClass::setTo(int inRed, int inGreen, int inBlue) 
{
  redVal = clipInRange(inRed);
  greenVal = clipInRange(inGreen);
  blueVal = clipInRange(inBlue);
 
}

// This function sets the color's component color values to the same as 
// those in the "inColor" input parameter.
// Input: a ColorClass
void ColorClass::setTo(ColorClass &inColor) 
{
  redVal = inColor.redVal;
  greenVal = inColor.greenVal;
  blueVal = inColor.blueVal;

}
