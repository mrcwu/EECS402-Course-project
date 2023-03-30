#ifndef _INTERSECTIONSIMULATIONCLASS_H_
#define _INTERSECTIONSIMULATIONCLASS_H_

#include <string>
//Note: not "using namespace std" in header files, so will have to
//      prepend all items from the std namespace with "std::" here
#include "SortedListClass.h"
#include "EventClass.h"

#include "FIFOQueueClass.h"
#include "CarClass.h"

//Programmer: Andrew Morgan
//Date: November 2020
//Purpose: A class that will act as the basis for an event-driven
//         simulation involving traffic flow through an intersection
//         that is managed via a traffic light.
class IntersectionSimulationClass
{
  private:
    //Overall state attributes:
    bool isSetupProperly; //Indicates whether this simulation object
                          //is set up properly and is expected to be
                          //in a state that is ready to run.

    //Simulation control parameter attributes:
    int randomSeedVal; //Seed value to use for the random number generator
    int timeToStopSim; //Time after which events aren't handled
    int eastWestGreenTime; //Number of "time tics" that the light
                           //will be green in the east-west direction
    int eastWestYellowTime; //Number of "time tics" that the light
                            //will be yellow in the east-west direction
    //Note: Not storing eastWestRedTime, because we don't want to store
    //      "compute-able data" and the EW red time is just the sum of
    //      the NS green and yellow times.
    int northSouthGreenTime; //Number of "time tics" that the light
                             //will be green in the north-south direction
    int northSouthYellowTime; //Number of "time tics" that the light
                              //will be yellow in the north-south direction
    //Note: Not storing northSouthRedTime, because we don't want to store
    //      "compute-able data" and the NS red time is just the sum of
    //      the EW green and yellow times.

    //The following attributes represent statistical distributions that
    //characterize how vehicles arrive at the intersection in the four
    //different directions.  Our analysis has shown that arrivals are 
    //best characterized by a Normal Distribution in each direction, but
    //the parameters of the Normal Distribution depends on the direction.
    //For example, cars may arrive heading north more frequently than
    //those heading east because the freeway on-ramp is to the north, etc.
    double eastArrivalMean;
    double eastArrivalStdDev;
    double westArrivalMean;
    double westArrivalStdDev;
    double northArrivalMean;
    double northArrivalStdDev;
    double southArrivalMean;
    double southArrivalStdDev;

    int percentCarsAdvanceOnYellow; //Percentage of cars that, when
                                    //reaching the traffic light in a
                                       //yellow state advance through the
                                       //intersection.  This is a value
                                       //from 0 to 100, so that 75 indicates
                                       //75% of the vehicles will advance on
                                       //yellow, and 25% will not.

    //Simulation execution attributes
    int currentTime; //The current time for the simulation
    int currentLight; //The state of the traffic light at the current sim time
    SortedListClass< EventClass > eventList; //The time-sorted list of events
                                             //currently scheduled to occur
    FIFOQueueClass< CarClass > eastQueue; //Queue of cars waiting to advance
                                          //through intersection east-bound
    FIFOQueueClass< CarClass > westQueue; //West-bound queue of cars
    FIFOQueueClass< CarClass > northQueue; //North-bound queue of cars
    FIFOQueueClass< CarClass > southQueue; //South-bound queue of cars

    //Statistics-Related attributes
    int maxEastQueueLength;
    int maxWestQueueLength;
    int maxNorthQueueLength;
    int maxSouthQueueLength;
    int numTotalAdvancedEast;
    int numTotalAdvancedWest;
    int numTotalAdvancedNorth;
    int numTotalAdvancedSouth;

    // custom print functions

    // this function will cout the required sentences and add up the incoming 
    // car into the assigned queue (curQueue) and maxQueueLength
    // Input: 
    // 1. string curDirectionUpIni: the current direction name with upper 
    // initial to modify (ex. North)
    // 2. string curDirectionLoIni: the current direction name with lower 
    // initial to modify (ex. north) 
    // 3. int& curTime: tell this function which is the variable that store the 
    // current time tic counting
    // 4. FIFOQueueClass<CarClass>& curQueue: the current direction queue to 
    // modify
    // 5. int& maxQueueLength: the current direction maxQueLength to modify
    void carArrival(string curDirectionUpIni, 
                    string curDirectionLoIni,
                    int& curTime,
                    FIFOQueueClass<CarClass>& curQueue,
                    int& maxQueueLength);

    // this function will deque the cars on queues and cout required sentences
    // while the light is going to be "yellow" (EVENT_CHANGE_YELLOW_XX).
    // Input:
    // first and second will effect the order on the cout sentence,
    // it must follow the sample output order. (ex. if the sentence on the 
    // sample is "east-west", the direction1 will be east and direction2 will be
    // west).
    // Since this function is focus on the forward and backward directions deque
    //  (ex. in the EW from green light to yellow), the directions will be the 
    // same as the event name (direction1 = east, direction2 = west while event 
    // name is EVENT_CHANGE_Yellow_EW).
    // 1. string direction1UpIni: the upper initial name of first direction 
    // 2. string direction2UpIni: the upper initial name of second direction 
    // 3. string direction1LoIni: the lower initial name of first direction 
    // 4. string direction2LoIni: the lower initial name of second direction 
    // 5. FIFOQueueClass<CarClass>& direction1Queue: the queue name of 
    // first direction
    // 6. FIFOQueueClass<CarClass>& direction2Queue: the queue name of
    // second direction
    // 7. int& numTotalAdvancedDirection1: the numTotalAdvanced variable name of
    // first direction
    // 8. int& numTotalAdvancedDirection2: the numTotalAdvanced variable name of
    // second direction
    // 9. int greenTime: the current forward and backward directions green light
    // time
    // 10. int changeCurLightTo: the light code after finishing modification. 
    // Name should be corresonded  to the event name 
    // (ex. "EVENT_CHANGE_YELLOW_EW" will be LIGHT_YELLOW_EW)
    void changeLightToYellow(string direction1UpIni,
                             string direction2UpIni,
                             string direction1LoIni,
                             string direction2LoIni,
                             FIFOQueueClass<CarClass>& direction1Queue,
                             FIFOQueueClass<CarClass>& direction2Queue,
                             int& numTotalAdvancedDirection1,
                             int& numTotalAdvancedDirection2,
                             int greenTime,
                             int changeCurLightTo);

    // this function is very similar changeLightToYellow. It will deque the cars
    //  on queues and cout required sentences while the light is going to be 
    // "green" however (EVENT_CHANGE_Green_XX).
    // Input:
    // First and second will effect the order on the cout sentence,
    // it must follow the sample output order. (ex. if the sentence on the 
    // sample is "east-west", the direction1 will be east and direction2 will be
    // west).
    // Since this function is focus on the crossing directions deque
    // (ex. the EW is yellow green light and then NS turn green), the directions
    //  will be different from the event name (direction1 = east, 
    // direction2 = west while event name is EVENT_CHANGE_Green_NS. The inputs
    // directions from 1 to 9 will be different from the EVENT_CHANGE_Green_XX).
    // 1. string direction1UpIni: the upper initial name of first direction 
    // 2. string direction2UpIni: the upper initial name of second direction 
    // 3. string direction1LoIni: the lower initial name of first direction 
    // 4. string direction2LoIni: the lower initial name of second direction 
    // 5. FIFOQueueClass<CarClass>& direction1Queue: the queue name of 
    // first direction
    // 6. FIFOQueueClass<CarClass>& direction2Queue: the queue name of
    // second direction
    // 7. int& numTotalAdvancedDirection1: the numTotalAdvanced variable name of
    // first direction
    // 8. int& numTotalAdvancedDirection2: the numTotalAdvanced variable name of
    // second direction
    // 9. int yellowTime: the current crossing directions yellow light time
    // 10. int changeCurLightTo: the light code after finishing modification. 
    // Name should be corresonded  to the event name 
    // (ex. "EVENT_CHANGE_GREEN_NS" will be LIGHT_GREEN_NS)
    void changeLightToGreen(string direction1UpIni,
                            string direction2UpIni,
                            string direction1LoIni,
                            string direction2LoIni,
                            FIFOQueueClass<CarClass>& direction1Queue,
                            FIFOQueueClass<CarClass>& direction2Queue,
                            int& numTotalAdvancedDirection1,
                            int& numTotalAdvancedDirection2,
                            int yellowTime,
                            int changeCurLightTo);

  public:
    //Explicit default ctor - sets the state of the sim to be NOT yet
    //setup properly.
    IntersectionSimulationClass()
    {
      isSetupProperly = false;
      //no need to initialize other params here, since the isSetupProperly
      //boolean is used to indicate the other params can't be trusted yet.

      //Set up the initial state of the simulation itself..
      currentTime = 0;
      currentLight = LIGHT_GREEN_EW;

      //Initialize stats
      maxEastQueueLength = 0;
      maxWestQueueLength = 0;
      maxNorthQueueLength = 0;
      maxSouthQueueLength = 0;
      numTotalAdvancedEast = 0;
      numTotalAdvancedWest = 0;
      numTotalAdvancedNorth = 0;
      numTotalAdvancedSouth = 0;
    }

    //Returns true if this simulation is ready to be executed, false otherwise.
    bool getIsSetupProperly(
         ) const
    {
      return isSetupProperly;
    }

    //Reads a full set of simulation control parameters from a text file.
    //When successful, the simulation object will have its control
    //parameter attributes assigned and will be put in the "properly
    //setup" state, indicating the simualtion can be run in its current
    //state.
    void readParametersFromFile(
         const std::string &paramFname //Name of text file to read params from
         );

    //Print the simulation control parameters to the console
    void printParameters(
         ) const;

    //Computes and returns the amount of time the light is red in the
    //east-west direction.
    int getEastWestRedTime(
         ) const
    {
      return northSouthGreenTime + northSouthYellowTime;
    }

    //Computes and returns the amount of time the light is red in the
    //north-south direction.
    int getNorthSouthRedTime(
         ) const
    {
      return eastWestGreenTime + eastWestYellowTime;
    }

    //Schedules the first car arrival in each direction to "seed" the
    //event driven simulation.
    void scheduleSeedEvents(
         )
    {
      scheduleArrival(EAST_DIRECTION);
      scheduleArrival(WEST_DIRECTION);
      scheduleArrival(NORTH_DIRECTION);
      scheduleArrival(SOUTH_DIRECTION);
      scheduleLightChange();
    }

    //Schedules an arrival event in the specified direction.
    void scheduleArrival(
         const std::string &travelDir
         );

    //Schedule a light change event to occur.
    void scheduleLightChange(
         );

    //Handles the next event scheduled in the simulation's event list.
    //Returns true if the event was handled, or false if the next
    //event's scheduled time occurs after the specified simulation end time.
    bool handleNextEvent(
         );

    //Prints the computed statistics from the simulation.
    void printStatistics(
         ) const;
};

#endif // _INTERSECTIONSIMULATIONCLASS_H_
