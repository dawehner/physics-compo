#ifndef ANOMALIE_CPP
#define ANOMALIE_CPP

#include <cmath>
#include "anomalie.h"
#include <iostream>

using namespace std;

/**
 * Generate the "extentrische anomalie" from certain "startbedingungen" with a certain iteration method.
 */
double generate_anomalie_excent(double excent, double anomalie_middle) {
  double anomalie_excent = anomalie_middle;
  double anomalie_excent_last = 0;

  int i = 0;
  double min = 10e-9;
  while ((fabs(anomalie_excent - anomalie_excent_last) > min) && i < 10000) {
    anomalie_excent_last = anomalie_excent;
    anomalie_excent = iteration_newton(anomalie_excent, excent, anomalie_middle);
    i++;
  }

  return anomalie_excent;
}

/**
 * Generate the "extentrische anomalie" based on a certain time, time t0 and perdionendauer.
 */
double generate_anomalie_excent_per_time(double excent, double t, double t0, double P) {
 // Generate a middle anomalie to calc with.
  double anomalie_middle = 2 * 3.1415926 * (t - t0) / (P);
  return generate_anomalie_excent(excent, anomalie_middle);
}

double iteration_newton(double anomalie_excent, double excent, double anomalie_middle) {
  double funcvalue = anomalie_excent - excent * sin(anomalie_excent) - anomalie_middle;
  double diffvalue =  1.0 - excent * cos(anomalie_excent);
  double result = anomalie_excent
    - (funcvalue / diffvalue);
  return result;
}

inline double anomalie_calc_phi(double anomalie_excent, double excent) {
  return 2 * atan(
     sqrt((1+excent)/(1-excent)) *
    tan(anomalie_excent / 2));
 }
inline double anomalie_calc_r(double a, double e, double phi, double phi0) {
  // phi0 is not used here.
  return (a * (1 - e * e)) / (1 + e * cos(phi - 0));
}

inline double anomalie_calc_x(double r, double phi, double phi0) {
  return r * cos(phi + phi0);
}

inline double anomalie_calc_y(double r, double phi, double phi0) {
  return r * sin(phi + phi0);
}

#endif