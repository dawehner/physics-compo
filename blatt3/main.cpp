#include <iostream>
#include <cmath>

#include "static_helper.h"
#include "integration.cpp"
#include "main.h"

using namespace std;


int main() {
  //double value = integrate_easy(&si, 0, x, 0.02);
  cout << "integration func_c" << endl;
  double value2 = integrate_adaptive(&func_c, 0, 5, 0.00001);
  cout << "Adaptive: " << value2 << " " << static_cache(STATIC_ADAPTIVE) << endl;
  double value3 = integrate_trapez_precision(&func_c, 0, 5, pow(10, -8));
  cout << "Trapez: " << value3 << " " << static_cache(STATIC_TRAPEZ_PRECISION) << endl;

  cout << "integration func_si" << endl;
  value2 = integrate_adaptive(&func_si, 0, 1, 0.0001);
  cout << "Adaptive: " << value2 << " " << static_cache(STATIC_ADAPTIVE) << endl;
  value3 = integrate_trapez_precision(&func_si, 0, 1, pow(10, -8));
  cout << "Trapez: " << value3 << " " << static_cache(STATIC_TRAPEZ_PRECISION) << endl;
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

