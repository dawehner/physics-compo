
#ifndef QUANTITIES_H
#define QUANTITIES_H

#include "quantities.cpp"

double calc_great_half_axis(vector2d& r, vector2d& v, vector< double>& m);
double calc_excentric(vector2d& r, vector2d& v, vector< double>& m, double& great_half_axis);
double calc_energy(listv2d r, listv2d v, listdouble m);
double calc_angular_momentum(std::vector< double >& m, double& great_half_axis, double& excentric);
double calc_periode(const listdouble& m);

vector2d calc_specific_angular_momentum(const vector2d& r, const vector2d& v);
vector2d calc_mass_center();
vector2d calc_runge_lenz(const vector2d& j, const vector2d& r, const vector2d& v, const listdouble& m);

double calc_mass_center(listv2d& r, listdouble& m, const double& total_mass);
double calc_total_mass(listdouble& m);

#endif
