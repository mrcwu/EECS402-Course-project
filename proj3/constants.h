#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <string>

#include <iostream>
using namespace std;

// GLOBAL CONSTANT DECLARING

// for ColorClass
const int MAX_COLOR_VALUE = 255;
const int MIN_COLOR_VALUE = 0;

const int RGB_LENGTH = 3; // the length of red, green, and blue pixel list
// RGB index in each pixel list
const int RED_IND = 0;
const int GREEN_IND = 1;
const int BLUE_IND = 2;


// for PatternClass
const int HAS_PIXEL = 1;
const int NO_PIXEL = 0;

// for Main
// Maxium number of characters to store in cin
const int MAX_CHAR_IN_CIN = 200;

// Magic number P3
const string MAGIC_NUMBER = "P3";

// Input selection default values
const int INPUT_SELECTION_DEFAULT_VALUE = 0;

// the main menu options
const int MENU_MAX_INDEX = 5;
const int ANNO_WITH_RECTANGLE = 1;
const int ANNO_WITH_PATTERN = 2;
const int INSERT_IMG = 3;
const int WRITE_OUT = 4;
const int EXIT_PROGRAM = 5;

// the sub menu options
const int SPECIFY_MENU_MAX_INDEX = 3;
const int SPECIFY_UL_LR = 1;
const int SPECIFY_UL_AND_DIMENTION = 2;
const int SPECIFY_EXT_FROM_CENTER = 3;

const int SPECIFY_UL_ONLY_PAT = 4;
const int SPECIFY_UL_ONLY_IMG = 5;

const int NO_YES_MENU_MAX_INDEX = 2;
const int NO = 1;
const int YES = 2;

// Color code
const int COLOR_MAX_INDEX = 5;
const int RED = 1;
const int GREEN = 2;
const int BLUE = 3;
const int BLACK = 4;
const int WHITE = 5;

// Custom color code
const int NOCOLOR = -99999;

#endif