#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "constants.h"

#include "CarClass.h"
#include "EventClass.h"

#include "IntersectionSimulationClass.h"
#include "FIFOQueueClass.h"
#include "SortedListClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
  int arriTime;
  EventClass arriEvent;

  if (travelDir == EAST_DIRECTION)
  {
    arriTime = getPositiveNormal(eastArrivalMean, eastArrivalStdDev);
    arriEvent = EventClass(arriTime + currentTime, EVENT_ARRIVE_EAST);
  }
  else if (travelDir == WEST_DIRECTION)
  {
    arriTime = getPositiveNormal(westArrivalMean, westArrivalStdDev);
    arriEvent = EventClass(arriTime + currentTime, EVENT_ARRIVE_WEST);
  }
  else if (travelDir == NORTH_DIRECTION)
  {
    arriTime = getPositiveNormal(northArrivalMean, northArrivalStdDev);
    arriEvent = EventClass(arriTime + currentTime, EVENT_ARRIVE_NORTH);
  }
  else if (travelDir == SOUTH_DIRECTION)
  {
    arriTime = getPositiveNormal(southArrivalMean, southArrivalStdDev);
    arriEvent = EventClass(arriTime + currentTime, EVENT_ARRIVE_SOUTH);
  }
  // print the stats sentence and schedule the event
  eventList.insertValue(arriEvent);
  cout << "Time: " <<  currentTime << " Scheduled " << arriEvent << endl;

}

void IntersectionSimulationClass::scheduleLightChange(
     )
{
  EventClass lightChangeEvent;

  if (currentLight == LIGHT_GREEN_EW)
  {
    lightChangeEvent = EventClass(eastWestGreenTime + currentTime, 
                                  EVENT_CHANGE_YELLOW_EW);
  }
  else if (currentLight == LIGHT_YELLOW_EW)
  {
    lightChangeEvent = EventClass(eastWestYellowTime + currentTime, 
                                  EVENT_CHANGE_GREEN_NS);
  }
  else if (currentLight == LIGHT_GREEN_NS)
  {
    lightChangeEvent = EventClass(northSouthGreenTime + currentTime, 
                                  EVENT_CHANGE_YELLOW_NS);
  }
  else if (currentLight == LIGHT_YELLOW_NS)
  {
    lightChangeEvent = EventClass(northSouthYellowTime + currentTime, 
                                  EVENT_CHANGE_GREEN_EW);
  }
  // print the stats sentence and schedule the event
  eventList.insertValue(lightChangeEvent);
  cout << "Time: " <<  currentTime << " Scheduled " << lightChangeEvent << endl;

}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
  EventClass curEvent; // to store the event currently facing

  // store the current event in the curEvent from the evenList, and remove the
  // front event (which has the lowest time tic in the list)
  eventList.removeFront(curEvent);

  // Normal cases: the current event's time does not exceed the end time
  if (curEvent.getTimeOccurs() <= timeToStopSim)
  {
    // setting the new current time to current event time
    currentTime = curEvent.getTimeOccurs();
    
    cout << endl;
    cout << "Handling " << curEvent << endl;

    // Car arrival east-bound (EVENT_ARRIVE_EAST)
    if (curEvent.getType() == EVENT_ARRIVE_EAST)
    {
      carArrival(EAST_DIRECTION, 
                  EAST_DIRECTION_LOWER_INI,
                  currentTime,
                  eastQueue,
                  maxEastQueueLength
                  );
    }

    // Car arrival west-bound (EVENT_ARRIVE_WEST)
    else if (curEvent.getType() == EVENT_ARRIVE_WEST)
    {
      carArrival(WEST_DIRECTION, 
                  WEST_DIRECTION_LOWER_INI,
                  currentTime,
                  westQueue,
                  maxWestQueueLength
                  );
    }

    // Car arrival north-bound (EVENT_ARRIVE_NORTH)
    else if (curEvent.getType() == EVENT_ARRIVE_NORTH)
    {
      carArrival(NORTH_DIRECTION, 
                  NORTH_DIRECTION_LOWER_INI,
                  currentTime,
                  northQueue,
                  maxNorthQueueLength
                  );
    }

    // Car arrival south-bound (EVENT_ARRIVE_SOUTH)
    else if (curEvent.getType() == EVENT_ARRIVE_SOUTH)
    {
      carArrival(SOUTH_DIRECTION, 
                  SOUTH_DIRECTION_LOWER_INI,
                  currentTime,
                  southQueue,
                  maxSouthQueueLength
                  );
    }

    // Light change from “Green in East-West” to “Yellow in East-West” 
    // (EVENT_CHANGE_YELLOW_EW)
    else if (curEvent.getType() == EVENT_CHANGE_YELLOW_EW)
    {
      changeLightToYellow(EAST_DIRECTION,
                          WEST_DIRECTION,
                          EAST_DIRECTION_LOWER_INI,
                          WEST_DIRECTION_LOWER_INI,
                          eastQueue,
                          westQueue,
                          numTotalAdvancedEast,
                          numTotalAdvancedWest,
                          eastWestGreenTime,
                          LIGHT_YELLOW_EW);
    }

    // Light change from “Yellow in East-West” to “Green in North-South” 
    // (EVENT_CHANGE_GREEN_NS)
    else if (curEvent.getType() == EVENT_CHANGE_GREEN_NS)
    {
      changeLightToGreen(EAST_DIRECTION,
                          WEST_DIRECTION,
                          EAST_DIRECTION_LOWER_INI,
                          WEST_DIRECTION_LOWER_INI,
                          eastQueue,
                          westQueue,
                          numTotalAdvancedEast,
                          numTotalAdvancedWest,
                          eastWestYellowTime,
                          LIGHT_GREEN_NS);
    }

    // Light change from “Green in North-South” to “Yellow in North-South” 
    // (EVENT_CHANGE_YELLOW_NS)
    else if (curEvent.getType() == EVENT_CHANGE_YELLOW_NS)
    {
      changeLightToYellow(NORTH_DIRECTION,
                          SOUTH_DIRECTION,
                          NORTH_DIRECTION_LOWER_INI,
                          SOUTH_DIRECTION_LOWER_INI,
                          northQueue,
                          southQueue,
                          numTotalAdvancedNorth,
                          numTotalAdvancedSouth,
                          northSouthGreenTime,
                          LIGHT_YELLOW_NS);
    }

    // Light change from “Yellow in North-South” to “Green in East-West” 
    // (EVENT_CHANGE_GREEN_EW)
    else if (curEvent.getType() == EVENT_CHANGE_GREEN_EW)
    {
      changeLightToGreen(NORTH_DIRECTION,
                          SOUTH_DIRECTION,
                          NORTH_DIRECTION_LOWER_INI,
                          SOUTH_DIRECTION_LOWER_INI,
                          northQueue,
                          southQueue,
                          numTotalAdvancedNorth,
                          numTotalAdvancedSouth,
                          northSouthYellowTime,
                          LIGHT_GREEN_EW);
    }

    // to keep on going, this method should return ture
    return true;
  }
  // Finish case: the current event's time exceeds the end time
  else
  {
    // print out the loop ending sentence
    cout << endl;
    cout << "Next event occurs AFTER the simulation end time ("
        << curEvent 
        << ")!" << endl;
    // end the runing loop
    return false;
  }

}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}

void IntersectionSimulationClass::carArrival(
                                  string curDirectionUpIni, 
                                  string curDirectionLoIni,
                                  int& curTime,
                                  FIFOQueueClass<CarClass>& curQueue,
                                  int& maxQueueLength
                                  )
{
  CarClass car(curDirectionUpIni, curTime);
  curQueue.enqueue(car);

  cout << "Time: " << curTime << " Car #"
       << car.getId() << " arrives " 
       << curDirectionLoIni << "-bound - queue length: "
       << curQueue.getNumElems() << endl;

  scheduleArrival(curDirectionUpIni);
  if (curQueue.getNumElems() > maxQueueLength)
  {
    maxQueueLength = curQueue.getNumElems();
  }
}


void IntersectionSimulationClass::changeLightToYellow(
                                  string direction1UpIni,
                                  string direction2UpIni,
                                  string direction1LoIni,
                                  string direction2LoIni,
                                  FIFOQueueClass<CarClass>& direction1Queue,
                                  FIFOQueueClass<CarClass>& direction2Queue,
                                  int& numTotalAdvancedDirection1,
                                  int& numTotalAdvancedDirection2,
                                  int greenTime,
                                  int changeCurLightTo) 
{
  int direction1Count = 0;
  int direction2Count = 0;
  CarClass car;
  
  // print out the first sentence
  cout << "Advancing cars on "<< direction1LoIni <<"-"
       << direction2LoIni << " green" << endl;

  // check the direction1 queue if it has anything
  if (direction1Queue.getNumElems() > 0)
  {
    while (direction1Count < greenTime &&
           direction1Queue.getNumElems() > 0)
    {
      direction1Queue.dequeue(car);
      cout << "  Car #" << car.getId()
           << " advances " << direction1LoIni << "-bound" << endl;

      direction1Count += 1;
    }
  }
  else
  {
    // print the required sentence if no car advance on green
    cout << "  No "<< direction1LoIni 
         <<"-bound cars waiting to advance on green" << endl;
  }
  
  // check the direction2 queue if it has anything
  if (direction2Queue.getNumElems() > 0)
  {
    while (direction2Count < greenTime &&
           direction2Queue.getNumElems() > 0)
    {
      direction2Queue.dequeue(car);
      cout << "  Car #" << car.getId()
           << " advances "<< direction2LoIni << "-bound" << endl;

      direction2Count += 1;
    }
  }
  else
  {
    // print the required sentence if no car advance on green
    cout << "  No "<< direction2LoIni 
         <<"-bound cars waiting to advance on green" << endl;
  }

  // print the stats sentences
  cout << direction1UpIni << "-bound cars advanced on green: " 
       << direction1Count << " Remaining queue: " 
       << direction1Queue.getNumElems() << endl;

  cout << direction2UpIni << "-bound cars advanced on green: " 
       << direction2Count << " Remaining queue: " 
       << direction2Queue.getNumElems() << endl;

  // change the current light and schedule the change
  currentLight = changeCurLightTo;
  scheduleLightChange();

  // add the number of advanced
  numTotalAdvancedDirection1 += direction1Count;
  numTotalAdvancedDirection2 += direction2Count;
}


void IntersectionSimulationClass::changeLightToGreen(
                                  string direction1UpIni,
                                  string direction2UpIni,
                                  string direction1LoIni,
                                  string direction2LoIni,
                                  FIFOQueueClass<CarClass>& direction1Queue,
                                  FIFOQueueClass<CarClass>& direction2Queue,
                                  int& numTotalAdvancedDirection1,
                                  int& numTotalAdvancedDirection2,
                                  int yellowTime,
                                  int changeCurLightTo)
{
  int direction1Count = 0;
  int direction2Count = 0;
  CarClass car;

  // print out the first sentence
  cout << "Advancing cars on " << direction1LoIni <<"-" 
       << direction2LoIni <<" yellow" << endl;

  // check the direction1 queue if it has anything
  if (direction1Queue.getNumElems() > 0)
  {
    // the indicator to stop the while loop of dequeue cars
    // since only partial of cars can escape during the yellow light
    bool stopIndicator = false;

    while (direction1Count < yellowTime &&
           stopIndicator == false &&
           direction1Queue.getNumElems() > 0)
    {
      // generate a random number between 1-100 to know whether the car can 
      // dequeue out or not
      if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
      {
        direction1Queue.dequeue(car);
        cout << "  Car #" << car.getId() << " advances " << direction1LoIni 
             <<"-bound" << endl;

        direction1Count += 1;
      }
      else
      {
        // print the required sentence if no car will advance on yellow
        if (direction1Count == 0)
        {
          cout 
          << "  Next "<< direction1LoIni 
          << "-bound car will NOT advance on yellow"
          << endl;
        }
        // stop the loop since the yellow light time is over
        stopIndicator = true;
      }
    }
  }
  else
  {
    cout << "  No "<< direction1LoIni 
         <<"-bound cars waiting to advance on yellow" << endl;
  }


  // check the direction2 queue if it has anything
  if (direction2Queue.getNumElems() > 0)
  {
    // the indicator to stop the while loop of dequeue cars
    // since only partial of cars can escape during the yellow light
    bool stopIndicator = false;

    while (direction2Count < yellowTime &&
           stopIndicator == false &&
           direction2Queue.getNumElems() > 0)
    {
      // generate a random number between 1-100 to know whether the car can 
      // dequeue out or not
      if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
      {
        direction2Queue.dequeue(car);
        cout << "  Car #" << car.getId()
            << " advances "<< direction2LoIni << "-bound" << endl;

        direction2Count += 1;
      }
      else
      {
        // print the required sentence if no car will advance on yellow
        if (direction2Count == 0)
        {
          cout 
          << "  Next " << direction2LoIni 
          << "-bound car will NOT advance on yellow" << endl;
        }
        // stop the loop since the yellow light time is over
        stopIndicator = true;
      }
    }
  }
  else 
  {
    cout 
    << "  No "<< direction2LoIni << "-bound cars waiting to advance on yellow"
    << endl;
  }

  // print the stats sentences
  cout << direction1UpIni << "-bound cars advanced on yellow: " 
       << direction1Count << " Remaining queue: " 
       << direction1Queue.getNumElems() << endl;

  cout << direction2UpIni << "-bound cars advanced on yellow: " 
       << direction2Count << " Remaining queue: " 
       << direction2Queue.getNumElems() << endl;

  // change the current light and schedule the change
  currentLight = changeCurLightTo;
  scheduleLightChange();

  // add the number of advanced
  numTotalAdvancedDirection1 += direction1Count;
  numTotalAdvancedDirection2 += direction2Count;
}