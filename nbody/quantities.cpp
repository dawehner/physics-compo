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
  int size = v.size();
  for (int i = 0; i < size; i++) {
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

vector2d calc_specific_angular_momentum(vector2d& r, vector2d& v) {
  vector2d j;
  j.x = 0.0;
  j.y = 0.0;
//   j.z = r.x * v.y - r.y * v.x;

  return j;
}

vector2d calc_runge_lenz(const vector2d& j, const vector2d& r, const vector2d& v, const listdouble& m) {
  vector2d R;
  R.x = 0.0;
  R.y = 0.0;
//   R.z = 0.0;

  return R;
}

vector2d calc_mass_center(listv2d& r, listdouble& m, const double& total_mass) {
  int size = r.size();
  vector2d mass_center;
  mass_center.x = 0.0;
  mass_center.y = 0.0;

  for (int i = 0; i < size; i++) {
    mass_center = mass_center + r[i] * m[i];
  }
  return mass_center / total_mass;
}

double calc_total_mass(listdouble& m) {
  double total_mass = 0.0;
  int size = m.size();
  for (int i = 0; i < size; i++) {
    total_mass += m[i];
  }

  return total_mass;
}


#endif