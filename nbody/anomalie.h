#ifndef ANOMALIE_H
#define ANOMALIE_H

double generate_anomalie_excent(double excent, double anomalie_middle);
double generate_anomalie_excent_per_time(double excent, double t, double t0, double P);
double iteration_newton(double anomalie_excent, double excent, double anomalie_middle);

inline double anomalie_calc_phi(double anomalie_excent, double excent);
inline double anomalie_calc_r(double a, double e, double phi, double phi0);
inline double anomalie_calc_x(double r, double phi, double phi0);
inline double anomalie_calc_y(double r, double phi, double phi0);

#endif