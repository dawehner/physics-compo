#ifndef ITERATION_H
#define ITERATION_H

#include <cmath>
#include <vector>
#include "vector.cpp"
#include <iostream>

using namespace std;


const int ITERATION_EULER = 0;
const int ITERATION_HEUN = 1;
const int ITERATION_RUNGE_KUTTA = 2;

const double G = 1;

inline vector2d calc_accel(const std::vector< vector2d >& r, const std::vector< double >& m, const unsigned int j);
void calc_accel_multiple(const std::vector< vector2d >& r, vector< vector2d >& a, const std::vector< double >& m);

void iteration_start(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m);
void iteration_next(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h,
  void (*method_r) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h),
  void (*method_v) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h));

void iteration_euler_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_euler_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_heun_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_heun_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_runge_kutta_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_runge_kutta_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);


#endif // ITERATION_H