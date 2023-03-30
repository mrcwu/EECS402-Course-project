#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_
#include <fstream>

#include <iostream>
using namespace std;

// This class contain the information describing a color and several methods
//  to write the color in the object of this class.
class ColorClass 
{
  private:
    int redVal;
    int greenVal;
    int blueVal;

    // clip adjusting funtion
    int clipInRange(int inVal);


  public:
    // constructor
    ColorClass();
    ColorClass(int inRed,int inGreen,int inBlue);

    // functions
    void setToBlack();
    void setToRed();
    void setToGreen();
    void setToBlue();
    void setToWhite();

    void setTo(int inRed, int inGreen, int inBlue);
    void setTo(ColorClass &inColor);

    // read from each pixel into color classes
    void readColor(ifstream &inFile);
    // write from each class into pixels
    void writeColor(ofstream &outFile);

    // get individual color values;
    int getRed();
    int getGreen();
    int getBlue();


};

#endif 