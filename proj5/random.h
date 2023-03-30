#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <cstdlib>
using namespace std;

//Programmer: Andrew M. Morgan
//Purpose: Provide some simple functionality to generate
//pseudo-random numbers for multiple distribution types.

//This is called once at the beginning of program execution
//to set the seed of the pseudo-random number generator.
void setSeed(
    const int seedVal
    );

//Returns an integer value from a uniform distribution 
//between the specified min and max values.
int getUniform(
     const int minVal,
     const int maxVal
     );

//Returns an integer drawn from a normal distribution
//described by the input mean and standard deviation
//values.  Note: this may not result in a truly proper
//normal distribution because it ensures that negative
//values are never returned!
int getPositiveNormal(
     const double meanVal,
     const double stdDev
     );

#endif // _RANDOM_H_
