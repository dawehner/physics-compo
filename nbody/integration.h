#include "vector.cpp"
#include <iostream>
using namespace std;

const int INTEGRATION_EULER = 0;
const int INTEGRATION_HEUN = 1;
const int INTEGRATION_RUNGE_KUTTA = 2;
const int INTEGRATION_VERLET = 3;
const int INTEGRATION_ANALYTIC = 4;
const int INTEGRATION_LEAPFROG = 5;

void integration_euler(listv3d& r, listv3d& v, listv3d& a, const listdouble& m, double h, double ti);
void integration_heun(listv3d& r, listv3d& v, listv3d& a, const listdouble& m, double h, double ti);
void integration_rk4(listv3d& r, listv3d& v, listv3d& a, const listdouble& m, double h, double ti);
void integration_leap_frog(listv3d& r, listv3d& v, listv3d& a, const listdouble& m, double h, double ti);
void integration_analytic(listv3d& r, listv3d& v, listv3d& a, const listdouble& m, double h, double ti);
void integration_verlet(listv3d& r, listv3d& v, listv3d& a, const listdouble& m, double h, double ti);

void calc_accel_multiple(const listv3d& r, listv3d& a, const vector<double>&m);
inline vector3d calc_accel(const listv3d& r, const listdouble m, const int j);