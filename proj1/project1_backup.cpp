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
const double LOWER_BALANCE_BOUND = 1000; // the lower balance boundary. 
// If the balance is lower than LOWER_BALANCE_BOUND, 
// it will consider using MIN_INT_RATE as interest rate.
const double UPPER_BALANCE_BOUND = 15000; // the upper balance boundary.
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


// // testing requirements for project 1 (start)
// #ifdef ANDREW_TEST
// #include "andrewTest.h"
// #else


// main function
int main() 
{
  // initialize variables for prompt questions
  double balanceAmt; // the current balance amount
  int numMonths; // the number of months to accrue interest
  char printResult; // user's answer whether to show month-by-month result
  bool doPrintEachMonth; // bool variable for printResult convert


  // Prompt to ask the user questions
  cout << "Enter the initial balance of the account: "; // ask balance amount
  cin >> balanceAmt;

  cout << "Enter the number of months to accrue interest: "; // ask number of months
  cin >> numMonths;

  cout << "Show month-by-month results - 'y' for yes, any other for no: "; // ask whether to show month-by-month result or not
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

  // run the accrue interest function
  accrueInterest(balanceAmt, numMonths, doPrintEachMonth);

  return 0;
}


// // testing requirements for project 1 (ending)
// #endif


// function 1: accrueInterest - to calculate the accrue interest
bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
     )
{
  // initialize local variables
  double initBalanceAmt = balanceAmt; // inital balance
  double totalIntAmt; // Total interest accrued


  // calculate the interest of all months 
  if ((numMonths >= 0) && (balanceAmt >= 0)) 
  {
    for (int curMonth = 0; curMonth < numMonths; curMonth++) // loop through all of the months
    {
      accrueOneMonthsInterest(balanceAmt, doPrintEachMonth); // calculate the interest in each month
    }

    totalIntAmt = balanceAmt - initBalanceAmt; // calculate total interest accrued

    // Print out the summary
    cout << "Interest accrued for "<< numMonths << " months!" << endl;
    cout << endl;
    cout << "Initial balance: " << initBalanceAmt << endl;
    cout << "Total interest accrued: " << totalIntAmt  << endl;
    cout << "Final balance: " << balanceAmt << endl;

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
      cout << "ERROR in accrueInterest: numMonths must be > 0, but the value " << 
              numMonths << " was provided!" << endl;
      cout << "Sorry, an error was detected.  Unable to provide results!" << endl;
    }

    return false;
  }

}


// function 2: accrueOneMonthsInterest - to calculate the interest per month, the core function inside funtion 1
bool accrueOneMonthsInterest(
     double &balanceAmt, 
     const bool doPrintInfo
     )
{
  // initialize local variables
  double initBalanceAmt = balanceAmt; // record the initial balance before adding the accrIntAmt
  double initIntRate; // initial interest rate
  double accrIntAmt; // interest accrued


  // calculate the interest per month
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

    // calculate the interest accrued and new balance
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
    cout << "ERROR in accrueOneMonthsInterest: balanceAmt must be >= 0, but the value " << 
            initBalanceAmt << " was provided!" << endl;
    cout << "Sorry, an error was detected.  Unable to provide results!" << endl;

    return false;
  }

}
