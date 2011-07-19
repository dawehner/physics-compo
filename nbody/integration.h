#include "vector.cpp"
#include <iostream>
using namespace std;

const int INTEGRATION_EULER = 0;
const int INTEGRATION_HEUN = 1;
const int INTEGRATION_RUNGE_KUTTA = 2;
const int INTEGRATION_VERLET = 3;
const int INTEGRATION_ANALYTIC = 4;
const int INTEGRATION_LEAPFROG = 5;

void integration_euler(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, double ti);
void integration_heun(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, double ti);
void integration_rk4(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, double ti);
void integration_leap_frog(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, double ti);
void integration_analytic(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, double ti);
void integration_verlet(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, double ti);

void calc_accel_multiple(const listv2d& r, listv2d& a, const vector<double>&m);
inline vector2d calc_accel(const listv2d& r, const listdouble m, const int j);