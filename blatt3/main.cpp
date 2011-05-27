#include <iostream>
#include <cmath>

#include "main.h"
#include "static_helper.cpp"

using namespace std;

const int STATIC_TRAPEZ = 0;
const int STATIC_TRAPEZ_PRECISION = 1;
const int STATIC_ADAPTIVE = 2;


int main() {
  //double value = integrate_easy(&si, 0, x, 0.02);
  cout << "integration func_c" << endl;
  double value1 = integrate_trapez(&func_c, 0, 5, 0.02);
  cout << value1 << " " << static_cache(STATIC_TRAPEZ) << endl;
  double value2 = integrate_adaptive(&func_c, 0, 5, 0.02);
  cout << value2 << " " << static_cache(STATIC_ADAPTIVE) << endl;
  double value3 = integrate_trapez_precision(&func_c, 0, 5, pow(10, -8));
  cout << value3 << " " << static_cache(STATIC_TRAPEZ_PRECISION) << endl;

  cout << "integration func_si" << endl;
  value1 = integrate_trapez(&func_si, 0, 1, 0.02);
  cout << value1 << " " << static_cache(STATIC_TRAPEZ) << endl;
  value2 = integrate_adaptive(&func_si, 0, 1, 0.02);
  cout << value2 << " " << static_cache(STATIC_ADAPTIVE) << endl;
  value3 = integrate_trapez_precision(&func_si, 0, 1, pow(10, -8));
  cout << value3 << " " << static_cache(STATIC_TRAPEZ_PRECISION) << endl;
  return 0;
}

double sinus(double x) {
  return sin(x);
}

double parabel(double x) {
  return x * x;
}

double gerade(double x) {
  return 1.0;
}

double func_si(double x) {
  // Lim x -> 0 = 1.
  if (x == 0) {
    return 1.0;
  }
  return sin(x) / x;
}

double func_c(double x) {
  return cos(M_PI * x * x / 2);
}

