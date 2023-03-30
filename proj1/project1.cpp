#include <iostream>
#include <cmath>
using namespace std;

// Programmer: Conan Wu
// Date: September 2022
// Purpose: Project 1 - Calculation of accured interest for a bank account


// declare global constants
const double MIN_INT_RATE = 0.0015; // minimum interest rate
const double MAX_INT_RATE = 0.004; // maximum interest rate
const double STD_INT_RATE = 0.00225; // standard interest rate
const double LOWER_BALANCE_BOUND = 1000; 
// If the balance is lower than LOWER_BALANCE_BOUND, 
// it will consider using MIN_INT_RATE as interest rate.
const double UPPER_BALANCE_BOUND = 15000;
// If the balance is higher than UPPER_BALANCE_BOUND, 
// it will consider using MAX_INT_RATE as interest rate.

// declare functions
bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
     );
bool accrueOneMonthsInterest(
     double &balanceAmt,
     const bool doPrintInfo
     );


// testing requirements for project 1 (start)
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else


// main function
int main() 
{
  // initialize variables
  double balanceAmt;
  int numMonths;
  char printResult;
  bool doPrintEachMonth; // bool variable for printResult converting
  double initBalanceAmt;
  double totalIntAmt;

  // Prompt to ask the user questions
  cout << "Enter the initial balance of the account: ";
  cin >> balanceAmt;

  cout << "Enter the number of months to accrue interest: ";
  cin >> numMonths;

  cout << "Show month-by-month results - 'y' for yes, any other for no: ";
  cin >> printResult;

  // Convert char input (printResult) into a bool value
  if (printResult == 'y')
  {
    doPrintEachMonth = true;
  } 
  else 
  {
    doPrintEachMonth = false;
  }

  // start the calculation
  initBalanceAmt = balanceAmt;
  if (accrueInterest(balanceAmt, numMonths, doPrintEachMonth))
  {
    totalIntAmt = balanceAmt - initBalanceAmt;

    // Print out the summary
    cout << "Interest accrued for "<< numMonths << " months!" << endl;
    cout << endl;
    cout << "Initial balance: " << initBalanceAmt << endl;
    cout << "Total interest accrued: " << totalIntAmt  << endl;
    cout << "Final balance: " << balanceAmt << endl;
  }

  return 0;
}


// testing requirements for project 1 (ending)
#endif


// function 1: accrueInterest - to calculate the accrue interest
bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
     )
{

  // start to calculate the interest of all months
  if ((numMonths >= 0) && (balanceAmt >= 0)) 
  {
    for (int curMonth = 0; curMonth < numMonths; curMonth++)
    {
      accrueOneMonthsInterest(balanceAmt, doPrintEachMonth);
    }

    return true;
  } 
  else 
  {
    if (balanceAmt < 0) // failure case 1: the balance amount is negative
    {
      accrueOneMonthsInterest(balanceAmt, doPrintEachMonth);
    }
    else // failure case 2: the number of months is negative
    {
      cout << "ERROR in accrueInterest: numMonths must be > 0, "
              "but the value " << numMonths << " was provided!" << endl;
      cout << "Sorry, an error was detected. "
              " Unable to provide results!" << endl;
    }

    return false;
  }

}


// function 2: accrueOneMonthsInterest - to calculate the interest per month
bool accrueOneMonthsInterest(
     double &balanceAmt, 
     const bool doPrintInfo
     )
{
  // initialize local variables
  double initBalanceAmt = balanceAmt;
  double initIntRate;
  double accrIntAmt;


  // start calculate the interest per month
  if (balanceAmt >= 0) 
  {
    // decide which initial interest rate to use
    if (initBalanceAmt < LOWER_BALANCE_BOUND) 
    {
      initIntRate = MIN_INT_RATE;
    } 
    else if (initBalanceAmt >= UPPER_BALANCE_BOUND) 
    {
      initIntRate = MAX_INT_RATE;
    } 
    else 
    {
      initIntRate = STD_INT_RATE;
    }

    accrIntAmt = initBalanceAmt * initIntRate;
    balanceAmt = initBalanceAmt + accrIntAmt;

    // print the result for a month
    if (doPrintInfo) 
    {
      cout << "Accruing interest for 1 month: " << endl;
      cout << "  Initial balance: " << initBalanceAmt << endl;
      cout << "  Initial rate: " << initIntRate << endl;
      cout << "  Interest accrued: " << accrIntAmt << endl;
      cout << "  New balance: " << balanceAmt << endl;
    }

    return true;
  } 
  else // failure case: the balance amount is negative
  {
    cout << "ERROR in accrueOneMonthsInterest: balanceAmt must be >= 0, "
            "but the value " << initBalanceAmt << " was provided!" << endl;
    cout << "Sorry, an error was detected.  Unable to provide results!" << endl;

    return false;
  }

}
