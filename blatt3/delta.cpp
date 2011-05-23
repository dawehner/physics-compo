#include <iostream>
#include <cmath>

using namespace std;

int main() {
  double val = 1.0;
  double step = 2.0;
  double potenz = 0.0;
  while ((val + step) != val) {
   step = pow(10, potenz);
   potenz--;
  }
  cout << potenz << endl;
  return 0;
}
