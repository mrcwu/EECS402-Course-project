#include "questionForPath.h"

#include <fstream>
#include <string>
#include "inPatternCheck.h"
#include "inPpmCheck.h"
#include "constants.h"

#include <iostream>
using namespace std;

// this is a function of loop to ask the file name. if no file match the name or
// the file is not correct, it will keep asking until fixed.
// Input: 
// 1. a string of question sentence to print
// 2. a string to let user specify and store the file name
// 3. a bool to specify whether the current question is asking for a ppm file
void questionForPath(string const questionSentence, 
                     string& inFileName,
                     bool const isPpmFile)
{
  ifstream filePathCheck;
  bool correctnessCheck;

  // 1. Ask the filename
  // if the input fail, it will keep asking for the file name.

  do 
  {
    // 1.1 Ask the filename as base ppm
    if (cin.fail()) // correction: change the !cin.fail() to cin.fail()
    {
      cin.clear();
      cin.ignore(MAX_CHAR_IN_CIN, '\n');
    }
    cout << questionSentence;
    cin >> inFileName;

    // 1.2 setup checking functions
    ifstream filePathCheck(inFileName.c_str());
    if (isPpmFile)
    {
      correctnessCheck = inPpmCheck(inFileName);
    }
    else
    {
      correctnessCheck = inPatternCheck(inFileName);
    }


    if (!filePathCheck) 
    {
      cout << "Error: The file name " << inFileName << " is not found. "
            << "Please try again." << endl;
    }
    else if (cin.fail())
    {
      cout << "Error: The string " << inFileName << " is invalid. "
            << "Please try again." << endl;
    }
    else if (!correctnessCheck)
    {
      cout << "Error: The file " << inFileName << " is either corrupted or " 
            << "not supported. "
            << "Please try again." << endl;
    }

  }
  while (cin.fail() || !filePathCheck || !correctnessCheck);


}
