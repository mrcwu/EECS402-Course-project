#include "CarClass.h"

#include <iostream>
using namespace std;

//Assign the static attribute used for auto-assigning unique ids
int CarClass::nextIdVal = 0;

ostream& operator<<(
     ostream& outStream,
     const CarClass &carToPrint
     )
{
  outStream << "Car id: " << carToPrint.uniqueId <<
               " traveling: " << carToPrint.travelDir <<
               " arrived: " << carToPrint.arrivalTime;

  return outStream;
}

