#include <cmath>

/**
 * @todo:
 *   Implement all this stuff for vector.cpp
 */

inline double calc_metrik(double r1[], double r2[]);
inline double calc_norm(double r[]);
double calc_big_a(double r[3], double v[3], double m[]);
double calc_e(double r[3], double v[3], double m[], double a);

double calc_big_a(double r[3], double v[3], double m[]) {
  return 1/(2/calc_norm(r) - pow(calc_norm(v), 2) / (G* (m[0] + m[1])));
}

double calc_e(double r[3], double v[3], double m[], double a) {
  double h= r[0] * v[1] - r[1] * v[0];
  return sqrt(1 - h*h/(G(m[0] + m[1])*a));
}

inline double calc_metrik(double r1[], double r2[]) {
  double sum = 0.0;
  for (int i = 0; i < 3; i++) {
    sum += pow(r1[i] - r2[i], 2);
  }
  return sqrt(sum);
}

inline double calc_norm(double r[]) {
  double sum = 0.0;
  for (int i = 0; i < 3; i++) {
    sum += pow(r[i], 2);
  }
  return sqrt(sum);
}
