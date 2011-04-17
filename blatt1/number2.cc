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
  double lambda;
};


double distince_sunsystem_objects(sunsystem_object obj1, double anomalie_excent1, sunsystem_object obj2, double anomalie_excent2) {
  double phi1, phi2;
  double r1, r2;
  double x1, x2;
  double y1, y2;

  phi1 = calc_phi(anomalie_excent1, obj1.e);
  r1 = calc_r(obj1.a, obj1.e, phi1, obj1.phi0);
  x1 = calc_x(r1, phi1, obj1.phi0);
  y1 = calc_y(r1, phi1, obj1.phi0);

  phi2 = calc_phi(anomalie_excent2, obj2.e);
  r2 = calc_r(obj2.a, obj2.e, phi2, obj2.phi0);
  x2 = calc_x(r2, phi2, obj2.phi0);
  y2 = calc_y(r2, phi2, obj2.phi0);

  return (x1- x2)*(x1- x2) + (y1 - y2)*(y1 - y2);
}

int main() {
  double t = 0;
  double distance;

  double earth_temp_except;
  double mars_temp_except;

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
  mars.a = 1.524;
  mars.e = 0.0934;
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

    mars_temp_except = generate_anomalie_excent_per_time(mars.e, t, t0, mars.p);
    earth_temp_except = generate_anomalie_excent_per_time(earth.e, t, t0, earth.p);

    distance = distince_sunsystem_objects(earth, earth_temp_except, mars, mars_temp_except);
  }

  return 0;
}