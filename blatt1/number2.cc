#include <cmath>
#include <iostream>
#include <fstream>
#include "anomalie.cc"
#include "coordinates.cc"
#include <string>

using namespace std;

const double anstromical_unit = 149598000;
const int day_seconds = 3600 * 24;
const int year_seconds = 3600 * 365 * 24;

struct sunsystem_object {
  double a;
  double e;
  double phi0;
  double m;
  double p;
  string name;
};

int main() {
  double t0 = 0;
  double t = t0;
  double temp_except;
  double excent;

  sunsystem_object earth;
  earth.name = "Earth";
  earth.a = 1.0;
  earth.e = 0.0167;
  earth.phi0 = grad_to_rad(102.95);
  earth.lambda = 100.46;
  earth.m = earth.lambda - earth.phi0;
  earth.p = year_seconds;

  sunsystem_object mars;
  mars.name = "Mars";
  mars.a_mars = 1.524;
  mars.e_mars = 0.0934;
  mars.phi0 = grad_to_rad(336.04);
  mars.lambda = 355.46;
  mars.m = mars.lambda - mars.phi0;
  mars.p = day_seconds * 779.94;

  // fstream plots;
  // plots.open("../plots.txt", ios::out);
  // plots.close();

  // let's choose not too many steps
  int size = 1000;
  int t0, starttime = - 20 * year_seconds;
  int endtime = 5 * year_seconds;
  // Let's start from 2000 - 20 years and go until 2000 + 5 year'
  for (signed int i = (starttime / size) ; i < (endtime / size); i++) {
    t = i * size;

    temp_except = generate_anomalie_excent_per_time(e_earth, t, t0, P);
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

  return 0;
}