#ifndef _QUESTIONFORLOC_H_
#define _QUESTIONFORLOC_H_
#include <string>
#include "ColorImageClass.h"

#include <iostream>
using namespace std;

// this is a function for asking the users what locations they want to insert
void questionForLoc(int& startRowIndex, int& startColIndex,
                    int& fullNumRow, int& fullNumCol,
                    ColorImageClass& baseImg, 
                    int const questionType);

#endif