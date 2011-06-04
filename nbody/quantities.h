
#ifndef QUANTITIES_H
#define QUANTITIES_H

#include "quantities.cpp"

double calc_great_half_axis(vector2d& r, vector2d& v, vector< double>& m);
double calc_excentric(vector2d& r, vector2d& v, vector< double>& m, double& great_half_axis);
double calc_energy(listv2d r, listv2d v, listdouble m);
double calc_angular_momentum(std::vector< double >& m, double& great_half_axis, double& excentric);
double calc_periode(const listdouble& m);

#endif
