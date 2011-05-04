#include <cmath>


const int ITERATION_EULER = 0;
const int ITERATION_HEUN = 1;
const int ITERATION_RUNGE_KUTTA = 2;

double iteration();
inline double iteration_euler(double yk, double h, double fk, double fk1);
inline double iteration_heun(double yk, double h, double fk, double fk1);
inline double iteration_runge_kutta_4();

inline double iteration_euler(double yk, double h, double fk, double fk1) {
  return yk + h * fk;
}

inline double iteration_heun(double yk, double h, double fk, double fk1) {
  double k1 = fk;
  double k2 = fk1;
  return yk + h/2 * (k1 + k2);
}

inline double iteration_runge_kutta_4() { }

double iteration(int method) {
  switch (method) {
    case ITERATION_EULER:
      break;
    case ITERATION_HEUN:
      break;
    case ITERATION_RUNGE_KUTTA:
      break;
  }
}