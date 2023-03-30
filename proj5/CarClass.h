#ifndef _CARCLASS_H_
#define _CARCLASS_H_

#include <iostream>
#include <string>

#include "constants.h"

//Programmer: Andrew Morgan
//Date: November 2020
//Purpose: A simple class to store data about a car participating in
//         a simualtion of traffic flow through an intersection.
//

class CarClass
{
  private:
    static int nextIdVal; //Static attribute used to auto-assign unique ids
    int uniqueId; //A unique identifier auto-assigned to each car
    std::string travelDir; //Direction this car object is traveling
    int arrivalTime; //The time at which the car arrived at the intersection

  public:
    //The primary ctor to be used when creating a new car. Will auto-assign
    //a unique identifier and store the car's travel direction.
    CarClass(
         const std::string inTravelDir,
         const int inArrivalTime
         )
    {
      uniqueId = nextIdVal;
      nextIdVal++;

      travelDir = inTravelDir;
      arrivalTime = inArrivalTime;
    }

    //An explicit default ctor that allows an "empty" car to be
    //created so that one can be declared in order to be passed
    //into a function by reference to be populated (such as
    //the FIFOQueueClass::dequeue method).
    CarClass(
         )
    {
      uniqueId = CAR_ID_NOT_SET;
    }

    //Simple getter for the car's unique id value attribute
    int getId(
         ) const
    {
      return uniqueId;
    }

    //Since this insertion operator really ought to be a method, but 
    //can't be due to the way C++ manages operator overloading, we
    //make it an "honorary method" by declaring it as a friend.
    friend std::ostream& operator<<(
                std::ostream& outStream,
                const CarClass &carToPrint
                );
};

//An overloaded insertion operator to allow a car object to be printed
//in a standard way...
std::ostream& operator<<(
     std::ostream& outStream,
     const CarClass &carToPrint
     );

#endif // _CARCLASS_H_
