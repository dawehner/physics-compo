
#ifndef QUANTITIES_H
#define QUANTITIES_H

#include "vector.cpp"
#include <vector>

#include "quantities.cpp"

double calc_great_half_axis(vector2d& r, vector2d& v, vector< double>& m);
double calc_excentric(vector2d& r, vector2d& v, vector< double>& m, double& great_half_axis);
double calc_energy(listv2d r, listv2d v, listdouble m);
double calc_angular_momentum(std::vector< double >& m, double& great_half_axis, double& excentric);
double calc_periode(const listdouble& m, double& great_half_axis, int j = 0);
double calc_t_max(double periode, double count_periods);

vector2d calc_specific_angular_momentum(const vector2d& r, const vector2d& v);
vector2d calc_mass_center(listv2d& r, listdouble& m, const double& total_mass);
vector2d calc_runge_lenz(const vector2d& j, const vector2d& r, const vector2d& v, const listdouble& m);


/**
 * Calculate the total mass of the system.
 *
 * @param j
 *   If this parameter is not 0 it's treated as two body system with j = second body index.
 */
double calc_total_mass(const listdouble& m, int j = 0);

#endif
