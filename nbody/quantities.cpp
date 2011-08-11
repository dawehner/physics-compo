#ifndef QUANTITIES_CPP
#define QUANTITIES_CPP

#include <cmath>

#include "vector.cpp"
#include <vector>

#include "quantities.h"


/**
 * Calculate the amount of time the simulation should run.
 *
 * @todo
 * Is this formula really what it should be?
 */
double calc_t_max(double periode, double count_periods) {
  return periode * count_periods;
}

double calc_great_half_axis(vector3d& j, double& total_mass, double& excentric) {
  return pow(norm(j), 2.0) / (total_mass * (1 - pow(excentric, 2.0)));
}

double calc_energy(listv3d r, listv3d v, listdouble m, int j) {
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

double calc_total_mass(const listdouble& m, int j) {
  double total_mass = 0.0;
  if (j == 0) {
    int size = m.size();
    for (int i = 0; i < size; i++) {
      total_mass += m[i];
    }
  }
  else {
    total_mass = m[0] + m[j];
  }

  return total_mass;
}

double calc_periode(const listdouble& m, double& great_half_axis, int j) {
  double total_mass = calc_total_mass(m, j);
  return 2 * M_PI / sqrt(1.0 * total_mass / pow(great_half_axis, 3.0));
//   return 1.0 / sqrt(1.0 * total_mass / pow(great_half_axis, 3.0));
}

vector3d calc_specific_angular_momentum(vector3d& r, vector3d& v) {
  return cross(r, v);
}

vector3d calc_runge_lenz(const vector3d& j, const vector3d& r, const vector3d& v, const double total_mass) {
  vector3d e;

  e = cross(v, j) / (1.0 * total_mass) - r / norm(r);

  return e;
}

vector3d calc_mass_center(listv3d& r, listdouble& m, const double& total_mass, int i = 0) {
  vector3d mass_center;
  mass_center.x = 0.0;
  mass_center.y = 0.0;
  mass_center.z = 0.0;

  mass_center = r[0] * m[0] + r[i] * m[i];

  return mass_center / total_mass;
}



#endif