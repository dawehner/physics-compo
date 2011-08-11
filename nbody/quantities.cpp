#ifndef QUANTITIES_CPP
#define QUANTITIES_CPP

#include <cmath>
#include "vector.cpp"
#include <vector>

/**
 * Calculate the amount of time the simulation should run.
 *
 * @todo
 * Is this formula really what it should be?
 */
double calc_t_max(double periode, double count_periods, double steps_per_orbit) {
  return count_periods * steps_per_orbit;
}

double calc_great_half_axis(vector3d& j, double& total_mass, double& excentric) {
  return pow(norm(j), 2.0) / (total_mass * (1 - pow(excentric, 2.0)));
}

double calc_energy(listv2d r, listv2d v, listdouble m, int j) {
  double energy_kinetic = 0.0;
  energy_kinetic += 0.5 * m[0] * pow(norm(v[0]), 2);
  energy_kinetic += 0.5 * m[j] * pow(norm(v[j]), 2);

  double energy_potential = - m[0] * m[j] / (norm(r[0] - r[j]));
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
  return cross(vector2d_3d(r), vector2d_3d(v));
}

vector3d calc_runge_lenz(const vector3d& j, const vector2d& r, const vector2d& v, const double total_mass) {
  vector3d e;

  vector3d r1 = vector2d_3d(r);
  vector3d v1 = vector2d_3d(v);

  e = cross(v1, j) / (1.0 * total_mass) - r1 / norm(r1);

  return e;
}

vector2d calc_mass_center(listv2d& r, listdouble& m, const double& total_mass, int i = 0) {
  vector2d mass_center;
  mass_center.x = 0.0;
  mass_center.y = 0.0;

  mass_center = r[0] * m[0] + r[i] * m[i];

  return mass_center / total_mass;
}

double calc_total_mass(listdouble& m, int j) {
  return m[0] + m[j];
}


#endif