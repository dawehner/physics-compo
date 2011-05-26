#include <iostream>
#include <cmath>

using namespace std;

double smallest_double() {
  double val = 1.0;
  while (1.0 + val != 1.0) {
    val *= 0.5;
  }
  return val;
}

void smallest_potenz() {
  double val = 1.0;
  double step = 2.0;
  double potenz = 0.0;
  while ((val + step) != val) {
   step = pow(10, potenz);
   potenz--;
  }

  cout << potenz << endl;
}

int main() {
  cout << smallest_double() << endl;
  return 0;
}
