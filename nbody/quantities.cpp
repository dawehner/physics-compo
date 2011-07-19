#ifndef QUANTITIES_CPP
#define QUANTITIES_CPP

#include <cmath>
#include "vector.cpp"
#include <vector>

double calc_t_max(double periode, double count_periods, double steps_per_orbit) {
  return count_periods * steps_per_orbit;
}

double calc_great_half_axis(vector2d& r, vector2d& v, const listdouble& m) {
  // @todo include G
  return pow(
    2/norm(r) - pow(norm(v), 2)/(m[0] + m[1])
  , -1);
}

double calc_excentric(vector2d& r, vector2d& v, const listdouble& m, double& great_half_axis) {
  // @todo include G
  double h = r.x * v.y - r.y * v.x;
  return sqrt(
    1 - pow(h, 2) / ((m[0] + m[1]) * great_half_axis)
  );
}

double calc_energy(listv2d r, listv2d v, listdouble m) {
  double energy_kinetic = 0.0;
  for (int i = 0; i < v.size(); i++) {
    energy_kinetic += 0.5 * m[i] * pow(norm(v[i]), 2);
  }
  double energy_potential = - m[0] * m[1] / (norm(r[0] - r[1]));
  return energy_potential + energy_kinetic;
}

double calc_angular_momentum(vector <double> & m, double& great_half_axis, double& excentric) {
  double M = m[0] + m[1];
  double mu = m[0] * m[1] / M;
  return mu * sqrt((1 - pow(excentric, 2)) * M * great_half_axis);
}

double calc_periode(const listdouble& m) {
  return 2 * M_PI / sqrt(m[0] + m[1]);
}

vector3d calc_specific_angular_momentum(vector2d& r, vector2d& v) {
  vector3d j;
  j.x = 0.0;
  j.y = 0.0;
  j.z = r.x * v.y - r.y * v.x;

  return j;
}

vector3d calc_runge_lenz(const vector3d& j, const vector2d& r, const vector2d& v, const listdouble& m) {
}

#endif