#include <cmath>
#include <iostream>
#include <fstream>
#include "anomalie.cc"
#include "coordinates.cc"

using namespace std;


int main() {
  double t = 0;
  double t0 = 0;
  double temp_except = 0;
  double excent = 0.205;
  double P = 10000;
  double phi = 0;
  double r = 0;
  double x = 0;
  double y = 0;
  double a = 1000;
  double phi0 = 102.95 * 3.1415926 / 180.0;

  // Generate 100 values of M
  double anomalie_middle = 0.0;
  double anomalie_excent = 0.0;
  for (int i = 0; i < 100; i++) {
    anomalie_middle = i;
    cout << i;
    anomalie_excent  = generate_anomalie_excent(excent, anomalie_middle);
    cout << endl;
  }

  return 0;
}