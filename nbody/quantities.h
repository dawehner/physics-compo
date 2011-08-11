
#ifndef QUANTITIES_H
#define QUANTITIES_H

#include "vector.cpp"
#include <vector>

#include "quantities.cpp"

double calc_great_half_axis(vector3d& r, vector3d& v, vector< double>& m);
double calc_excentric(vector3d& r, vector3d& v, vector< double>& m, double& great_half_axis);
double calc_energy(listv3d r, listv3d v, listdouble m);
double calc_angular_momentum(std::vector< double >& m, double& great_half_axis, double& excentric);
double calc_periode(const listdouble& m, double& great_half_axis, int j = 0);
double calc_t_max(double periode, double count_periods);

vector3d calc_specific_angular_momentum(const vector3d& r, const vector3d& v);
vector3d calc_mass_center(listv3d& r, listdouble& m, const double& total_mass);
vector3d calc_runge_lenz(const vector3d& j, const vector3d& r, const vector3d& v, const listdouble& m);


/**
 * Calculate the total mass of the system.
 *
 * @param j
 *   If this parameter is not 0 it's treated as two body system with j = second body index.
 */
double calc_total_mass(const listdouble& m, int j = 0);

#endif
