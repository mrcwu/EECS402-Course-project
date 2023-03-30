#include "questionForColor.h"

#include <fstream>
#include <string>
#include "printInvalidInNum.h"
#include "constants.h"

#include <iostream>
using namespace std;


// this is a function for asking the users what color they want
// Input: a string to give the object name that will be print in the question 
// message, a int to specify and store the user's color preference
void questionForColor(string const objectNameInQuestion, 
                      int& colorSelected) 
{
  do 
  {
    if (cin.fail())
    {
      cin.clear();
      cin.ignore(MAX_CHAR_IN_CIN, '\n');
    }

    cout << "1. Red" << endl;
    cout << "2. Green" << endl;
    cout << "3. Blue" << endl;
    cout << "4. Black" << endl;
    cout << "5. White" << endl;
    cout << "Enter int for " << objectNameInQuestion << " color: ";

    cin >> colorSelected;

    // if the input is invalid, it will show error message
    printInvalidInNum(!((colorSelected > 0) && 
                        (colorSelected <= COLOR_MAX_INDEX))|| 
                         cin.fail());

  }
  while (!((colorSelected > 0) && (colorSelected <= COLOR_MAX_INDEX))|| 
            cin.fail());
}
