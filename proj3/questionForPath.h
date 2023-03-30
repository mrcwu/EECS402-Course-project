#ifndef _QUESTIONFORPATH_H_
#define _QUESTIONFORPATH_H_
#include <string>

#include <iostream>
using namespace std;


// this is a function of loop to ask the file name. if no file match the name or
// the file is not correct, it will keep asking until fixed.
void questionForPath(string const questionSentence, 
                     string& inFileName,
                     bool const isPpmFile);
                     

#endif