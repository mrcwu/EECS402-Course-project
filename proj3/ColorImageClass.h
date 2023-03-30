#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_
#include <fstream>
#include <string>

#include "ColorClass.h"
#include "PatternClass.h"

#include <iostream>
using namespace std;

// this is a class to represent a image. There are some methods contained
// inside to adjust and set the image.
class ColorImageClass 
{
  private:
    ColorClass** imgMatrix;
    int imgRow;
    int imgCol;
    int imgMaxColor;

    // create dynamic allocation matrix function
    void createMatrix(int inRow, int inCol);
    // set specific location to a given pixel
    void setColorAtLocation(int inRowIndex, 
                            int inColIndex, 
                            ColorClass& inColor);
    // extract from a specific location to a pixel
    void getColorAtLocation(int inRowIndex, 
                            int inColIndex, 
                            ColorClass& outColor);

  public:
    // constructor
    ColorImageClass(int inRow, int inCol, int inColorNum);
    ColorImageClass(string fileName);

    // destructor
    ~ColorImageClass();

    // checking function
    bool isValidLoc(int startRowIndex, int startColIndex, int inRow, int inCol);

    // get row, column, and max color number
    int getRow();
    int getCol();
    int getMaxColor();

    // create a image
    void readImage(string fileName); // import from a ppm file 
    void createFilledRectangle(int inRow, int inCol, int inColorNum);

    // export the current image
    void writeImage(ofstream& outFile);

    // adjustment functions
    void insertImageFrom(ColorImageClass& inImg, 
                         int const startRowIndex, 
                         int const startColIndex,
                         int const transColor);
    
    void insertPatternFrom(PatternClass& inPat,
                           int const startRowIndex, 
                           int const startColIndex);


};

#endif