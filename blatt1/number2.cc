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
  
  // fstream plots;
  // plots.open("../plots.txt", ios::out);
  for (int i = 0; i < 100000; i++) {
    t += i * 0.00005;

	  temp_except = generate_anomalie_excent_per_time(excent, t, t0, P);
	  phi = calc_phi(temp_except, excent);
    r = calc_r(a, excent, phi, phi0);
    x = calc_x(r, phi, phi0);
    y = calc_y(r, phi, phi0);

    cout<<"r" << r;
    cout<<"phi" << phi << endl;

    // std::cout<<"x" << x;
    // std::cout<<"y" << y;
    // plots << x << ";" << y << endl;
  }
  // plots.close();

  return 0;
}