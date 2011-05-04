#include <cmath>

/**
 * Generate some variables.
 */
inline double calc_phi(double anomalie_excent, double excent) {
  return 2 * atan(
     sqrt((1+excent)/(1-excent)) *
    tan(anomalie_excent / 2));
 }
inline double calc_r(double a, double e, double phi, double phi0) {
  // phi0 is not used here.
  return (a * (1 - e * e)) / (1 + e * cos(phi - 0));
}

inline double calc_x(double r, double phi, double phi0) {
  return r * cos(phi + phi0);
}

inline double calc_y(double r, double phi, double phi0) {
  return r * sin(phi + phi0);
}

inline double grad_to_rad(double grad) {
  return M_PI * grad / 180.0;
}
