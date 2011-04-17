#include <cmath>
#include <iostream>
#include <fstream>
#include "anomalie.cc"
#include "coordinates.cc"

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
};

int main() {
  double t0 = 0;
  double t = t0;
  double temp_except;
  double excent;

  double a_earth = 1.0;
  double e_earth = 0.0167;
  double phi0_earth = grad_to_rad(102.95);
  double lambda_earth = 100.46;
  double m_earth = lambda_earth - phi0_earth;
  double p_earth = year_seconds;

  double a_mars = 1.524;
  double e_mars = 0.0934;
  double phi0_mars = grad_to_rad(336.04);
  double lambda_mars = 355.46;
  double m_mars = lambda_mars - phi0_mars;
  double p_mars = day_seconds * 779.94;

  // fstream plots;
  // plots.open("../plots.txt", ios::out);
  // plots.close();

  // let's choose not too many steps
  int size = 1000;
  int starttime = - 20 * year_seconds;
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