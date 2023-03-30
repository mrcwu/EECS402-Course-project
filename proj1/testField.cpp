#include <iostream>
using namespace std;

// testing field
bool testing();

int main()
{
  // bool x;
  // cout << "put the text for bool x: ";
  // cin >> x;
  // cout << x << endl;
  // int a;
  // int b;
  // a = b = 1;
  // cout << a << endl;
  // cout << b << endl;

  // a = 2;
  // cout << a << endl;
  // cout << b << endl;
  // char printResult;
  // cout << "Show month-by-month results - 'y' for yes, any other for no: "; // ask whether to show month-by-month result or not
  // cin >> printResult;
  // cout << printResult << endl;

  // bool a = testing();

  // if (!a) 
  // {
  //   cout << "finish" << endl;
  // }
  int numMonths = 3;
  for (int curMonth = 0; curMonth < numMonths; curMonth++)
      {
        cout << testing() << endl; // calculate the interest in each month
      }

  return 0;
}


bool testing () 
{
  cout << "print something" << endl;
  return false;
}
