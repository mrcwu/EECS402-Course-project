#include <cstdlib>
using namespace std;

#include "random.h"

void setSeed(
    const int seedVal
    )
{
  srand(seedVal);
}

int getUniform(
     const int minVal,
     const int maxVal
     )
{
  int uniRand;
  uniRand = rand() % ((maxVal + 1) - minVal) + minVal;
  return (uniRand);
}

int getPositiveNormal(
     const double meanVal,
     const double stdDev
     )
{
  const int NUM_UNIFORM = 12;
  const int MAX = 1000;
  const double ORIGINAL_MEAN = NUM_UNIFORM * 0.5;
  double sum;
  double standardNormal;
  double newNormal;
  int uni;

  sum = 0;
  for (int i = 0; i < NUM_UNIFORM; i++)
  {
    uni = rand() % (MAX + 1);
    sum += uni;
  }
  sum = sum / MAX;
  standardNormal = sum - ORIGINAL_MEAN;
  newNormal = meanVal + stdDev * standardNormal;

  //The purpose of this function is to get a POSITIVE integer, so
  //if the computed value ends up being negative, just flip the
  //sign.  Not ideal since the result won't necessarily be a
  //true normal distribution, but this will suffice for our purpose.
  if (newNormal < 0)
  {
    newNormal *= - 1;
  }
  return ((int)newNormal);
}
