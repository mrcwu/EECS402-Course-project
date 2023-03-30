#ifndef _EVENTCLASS_H_
#define _EVENTCLASS_H_

#include <iostream>

#include "constants.h"

//Programmer: Andrew Morgan
//Date: November 2020
//Purpose: A simple class to represent event objects that can be used in
//         an event-driven simulation.  The overloaded insertion operator
//         for this class ties it to a simulation of traffic flow through
//         an intersection managed by a traffic light, but the rest of
//         the class is intended to be more generic to represent events
//         in most event-driven simulations.

//Programmer: Conan Wu
//Date: Dec 2022
//Purpose: add up new overload operators in line 65 to 87

class EventClass
{
  private:
    int timeOccurs; //Time at which the event is scheduled to occur.
    int typeId; //This EventClass is used to represent any type of event
                //used by our simulation, so this typeId indicates what
                //kind of event this event object represents.

  public:
    //The primary ctor to be used when creating new events.
    EventClass(
         int inTimeOccurs,
         int inTypeId
         )
    {
      timeOccurs = inTimeOccurs;
      typeId = inTypeId;
    }

    //An explicit default ctor that allows an "empty" event to be
    //created so that one can be declared in order to be passed
    //into a function by reference to be populated (such as
    //the SortedListClass::removeFront method).
    EventClass(
         )
    {
      timeOccurs = EVENT_UNKNOWN;
      typeId = EVENT_UNKNOWN;
    }

    //Simple getter for the event's time attribute
    int getTimeOccurs(
         ) const
    {
      return timeOccurs;
    }

    //Simple getter for the event's type attribute
    int getType(
         ) const
    {
      return typeId;
    }

    //Remember to implement whichever overloaded operators your
    //SortedListClass needs in order to sort event class objects
    //here!  An event "A" is "less than" an event "B" if
    //"A"'s time is less than "B"'s time.

    bool operator > (const EventClass in) const
    {
      return timeOccurs > in.getTimeOccurs();
    }

    bool operator < (const EventClass in) const
    {
      return timeOccurs < in.getTimeOccurs();
    }

    bool operator >= (const EventClass in) const
    {
      return timeOccurs >= in.getTimeOccurs();
    }

    bool operator <= (const EventClass in) const
    {
      return timeOccurs <= in.getTimeOccurs();
    }

    //Since this insertion operator really ought to be a method, but 
    //can't be due to the way C++ manages operator overloading, we
    //make it an "honorary method" by declaring it as a friend.
    friend std::ostream& operator<<(
                std::ostream& outStream,
                const EventClass &eventToPrint
                );
};

//An overloaded insertion operator to allow an event object to be printed
//in a standard way...
std::ostream& operator<<(
     std::ostream& outStream,
     const EventClass &eventToPrint
     );

#endif // _EVENTCLASS_H_
