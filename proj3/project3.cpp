#include <fstream>
#include <string>
// the classes that is going to use
#include "ColorClass.h" 
#include "ColorImageClass.h"
#include "PatternClass.h"
// the global constant that is going o use
#include "constants.h"
// the functions that is going to use
#include "questionForPath.h"
#include "questionForColor.h"
#include "questionForLoc.h"
#include "printInvalidInNum.h"
#include "inPatternCheck.h"
#include "inPpmCheck.h"

#include <iostream>
using namespace std;

// Programmer: Conan Wu
// Date: November 3, 2022
// Project 3
// Purpose: 
// 1. import a ppm base image
// 2. modify by inserting a rectangle, pattern, or another ppm image
// 3. save and export the modified image


int main() 
{
  // 1. ask the filename
  string inputFileName;
  string mainQ1Sentence = "Enter string for PPM image file name to load: ";
  bool isBaseImgPpm = true; 

  questionForPath(mainQ1Sentence, inputFileName, isBaseImgPpm);

  // 2. build up the base ppm image if the filename is ok
  ColorImageClass baseImg(inputFileName);

  // 3. get into the editing loop
  // a bool to specify whether the user is exiting or not
  bool isExit = false;

  while (!isExit)
  {
    // set the input selection to default value
    int inputSelection = INPUT_SELECTION_DEFAULT_VALUE;

    // get into the Menu loop, if user specify the number wrong, it will keep 
    // asking until the number is correct
    do
    {
      if (cin.fail())
      {
        cin.clear();
        cin.ignore(MAX_CHAR_IN_CIN, '\n');
      }
      cout << "1. Annotate image with rectangle" << endl;
      cout << "2. Annotate image with pattern from file" << endl;
      cout << "3. Insert another image" << endl;
      cout << "4. Write out current image" << endl;
      cout << "5. Exit the program" << endl;
      cout << "Enter int for main menu choice:";
      cin >> inputSelection;

      printInvalidInNum(!((inputSelection > INPUT_SELECTION_DEFAULT_VALUE) && 
                             (inputSelection <= MENU_MAX_INDEX)) || cin.fail());

    }
    while (!((inputSelection > INPUT_SELECTION_DEFAULT_VALUE) && 
             (inputSelection <= MENU_MAX_INDEX)) || cin.fail());


    // get into different options according to the input selection

    // if user choose to annotate with rectangle
    if (inputSelection == ANNO_WITH_RECTANGLE) 
    {

      // the loop to ask the sub question about how to specify the locations 
      do
      {
        if (cin.fail())
        {
          cin.clear();
          cin.ignore(MAX_CHAR_IN_CIN, '\n');
        }

        cout << "1. Specify upper left and lower right corners of rectangle" 
              << endl;
        cout << "2. Specify upper left corner and dimensions of rectangle" 
              << endl;
        cout << "3. Specify extent from center of rectangle" 
              << endl;
        cout << "Enter int for rectangle specification method: ";

        cin >> inputSelection;


        printInvalidInNum(!((inputSelection > INPUT_SELECTION_DEFAULT_VALUE) 
                            && (inputSelection <= SPECIFY_MENU_MAX_INDEX)) || 
                            cin.fail());

      }
      while (!((inputSelection > INPUT_SELECTION_DEFAULT_VALUE) && 
               (inputSelection <= SPECIFY_MENU_MAX_INDEX)) || cin.fail());


      // variables for the first question
      int startRowIndex;
      int startColIndex;
      int fullNumRow;
      int fullNumCol;

      // the first question: the method and loc to draw the rectangle
      questionForLoc(startRowIndex, startColIndex,
                     fullNumRow, fullNumCol,
                     baseImg, 
                     inputSelection);


      // the second question: ask the fill in color
      // variable for the second question 
      int colorSelected = NOCOLOR;
      string objectName = "rectangle";

      questionForColor(objectName, colorSelected);


      // the third question: ask whether to fill in or not
      // variable for the third question
      int fillOption;
      
      do 
      {
        cin.clear();
        cin.ignore(MAX_CHAR_IN_CIN, '\n');

        cout << "1. No" << endl;
        cout << "2. Yes" << endl;
        cout << "Enter int for rectangle fill option: ";
        cin >> fillOption;

        // if the input is invalid, it will show error message
        printInvalidInNum(!((fillOption > 0) && 
                            (fillOption <= NO_YES_MENU_MAX_INDEX)) || 
                            cin.fail());

      } while (!((fillOption > 0) && (fillOption <= NO_YES_MENU_MAX_INDEX)) || 
                  cin.fail());


      // Final: build up the rectangle and insert into base ppm image
      // if fillOption is yes then create a colorImgClass
      if (fillOption == YES) // create a colorImgClass rectangle
      {
        // create the rectangle
        ColorImageClass rectangleToInsert(fullNumRow, 
                                          fullNumCol, 
                                          colorSelected);
        // insert the rectangle into base image
        baseImg.insertImageFrom(rectangleToInsert, 
                                startRowIndex, 
                                startColIndex, 
                                NOCOLOR);
      }
      else if (fillOption == NO) // create a pattern rectangle
      {
        // create the rectangle
        PatternClass rectangleToInsert(fullNumRow, fullNumCol, colorSelected);
        // insert the rectangle
        baseImg.insertPatternFrom(rectangleToInsert, 
                                  startRowIndex, 
                                  startColIndex);
      }

    }

    // if user choose to annotate with pattern
    else if (inputSelection == ANNO_WITH_PATTERN) 
    {
      // first question: ask the pattern filename
      string patFileName;
      string annoWithPatQ1Sen = "Enter string for file name "
                                "containing pattern: ";
      bool isPatPpm = false; 

      questionForPath(annoWithPatQ1Sen, patFileName, isPatPpm);

      
      // second question: ask pattern annotate location
      int patStartRowIndex;
      int patStartColIndex;
      int patFullNumRow;
      int patFullNumCol;

      ifstream inTempFile;
      inTempFile.open(patFileName.c_str());
      // the first row have 2 numbers row and col, stored them into local vars
      inTempFile >> patFullNumRow;
      inTempFile >> patFullNumCol;


      questionForLoc(patStartRowIndex, patStartColIndex,
                     patFullNumRow, patFullNumCol,
                     baseImg, 
                     SPECIFY_UL_ONLY_PAT);
    

      // third question: ask the color
      int colorSelected = NOCOLOR;
      string objectName = "pattern";

      questionForColor(objectName, colorSelected);


      // build up the pattern class and insert it into base image
      PatternClass patternToInsert(patFileName, colorSelected);

      baseImg.insertPatternFrom(patternToInsert, 
                                patStartRowIndex, 
                                patStartColIndex);

      
    }


    // 3.3. if user choose to insert PPM image
    else if (inputSelection == INSERT_IMG) 
    {
      // first question: ask the ppm file name
      string insertPpmFileName;
      string annoWithPpmQ1Sent = "Enter string for file name "
                                 "of PPM image to insert: ";
      bool isInsertPpmPpm = true; 

      questionForPath(annoWithPpmQ1Sent, insertPpmFileName, isInsertPpmPpm);


      // build up the insert ppm image if the filename is ok
      ColorImageClass insImg(insertPpmFileName);


      // second question: ask the row col locations to insert
      int insImgStartRowIndex;
      int insImgStartColIndex;
      int insImgFullNumRow = insImg.getRow();
      int insImgFullNumCol = insImg.getCol();

      questionForLoc(insImgStartRowIndex, insImgStartColIndex,
                     insImgFullNumRow, insImgFullNumCol,
                     baseImg, 
                     SPECIFY_UL_ONLY_IMG);


      // third question: ask transparecy color
      int colorSelected = NOCOLOR;
      string objectName = "transparecy";

      questionForColor(objectName, colorSelected);

      // insert the image
      baseImg.insertImageFrom(insImg, 
                              insImgStartRowIndex, 
                              insImgStartColIndex, 
                              colorSelected);

    }


    // if user choose to write out the file
    else if (inputSelection == WRITE_OUT) 
    {
      string outFileName;

      do 
      {
      cin.clear();
      cin.ignore(MAX_CHAR_IN_CIN, '\n');
      cout << "Enter string for PPM file name to output: ";
      cin >> outFileName;

      // if the input is invalid, it will show error message
      printInvalidInNum(cin.fail());

      }
      while (cin.fail());

      // if the outFileName is correct, generate the output
      ofstream outFile;

      outFile.open(outFileName.c_str());
      baseImg.writeImage(outFile);
      outFile.close();
    
    }


    // if user choose to exit the program
    else if (inputSelection == EXIT_PROGRAM) 
    {
      isExit = true;
      cout << "Thank you for using this program" << endl;
    }

  };


  return 0;
}






