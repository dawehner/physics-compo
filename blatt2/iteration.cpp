#include <cmath>
#include <vector>
#include "vector.cpp"
#include <iostream>

using namespace std;

const int ITERATION_EULER = 0;
const int ITERATION_HEUN = 1;
const int ITERATION_RUNGE_KUTTA = 2;

const double G = 1;

void iteration_next(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h,
  void (*method_r) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h),
  void (*method_v) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h));

void iteration_euler_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_euler_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_heun_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_heun_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_runge_kutta_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);
void iteration_runge_kutta_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h);


vector2d calc_accel(vector< vector2d >& r, std::vector< double >& m, unsigned int j);

void iteration_next(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h,
  void (*method_r) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h),
  void (*method_v) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h)) {
  // First calc all new r's based on the given method.
  // @todo is this really a copy?
  vector< vector2d > rk = r;
  // Therefore it's important not to use the new r's for the calculation of the new v's.
  method_r(r, v, a, m, h);

  // Then calc all new v's based on the given method.
  method_v(r, v, a, m, h);

  // Recall all a's.
   for (vector< vector<int> >::size_type i = 0; i < a.size(); i++) {
      a[i] = calc_accel(r, m, i);
   }
}


vector2d calc_accel(vector<vector2d>& r, vector<double>& m, unsigned j) {
  vector2d a;
  for (vector< vector<int> >::size_type i = 0; i < r.size(); i++) {
    if (i != j) {
      a = a + ((r[j] - r[i]) / pow(norm(r[j] - r[i]), 3)) * G * m[i] * m[j];
    }
  }

  a = - 1 * a / m[j];
  return a;
}


void iteration_euler_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h) {
  for (vector< vector<int> >::size_type i = 0; i < r.size(); i++) {
    // Calculate the next value for r.
    r[i] = r[i] + h * v[i];
  }
}

void iteration_euler_v (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h) {
  for (vector< vector<int> >::size_type i = 0; i < v.size(); i++) {
    // Calculate the next value for v.
    v[i] = v[i] + h * a[i];
  }
}

void iteration_heun_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double h) {
  vector <vector2d> r_tmp_next = r;
  iteration_euler_r(r_tmp_next, v, a, m, h);
  vector <vector2d> v_tmp_next = v;
  iteration_heun_v(r_tmp_next, v_tmp_next, a, m, h);
  for (vector< vector<int> >::size_type i = 0; i < r.size(); i++) {
    r[i] = r[i] + (h/2) * (v[i] + v_tmp_next[i]);
  }
}

void iteration_heun_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double h) {
  vector <vector2d> v_tmp_next = v;
  iteration_euler_v(r, v_tmp_next, a, m, h);
  vector <vector2d> r_tmp_next = v;
  iteration_euler_r(r_tmp_next, v_tmp_next, a, m, h);

  vector2d ai_tmp_next;
  for (vector< vector<int> >::size_type i = 0; i < v.size(); i++) {
    ai_tmp_next = calc_accel(r_tmp_next, m, i);
    v[i] = v[i] + (h/2) * (a[i] + ai_tmp_next);
  }
}

void calc_accel_multiple(vector< vector2d>& r, vector< vector2d>& a, vector<double>&m) {
  for (vector< vector<int> >::size_type i = 0; i < a.size(); i++) {
    a[i] = calc_accel(r, m, i);
  }
}

void iteration_runge_kutta_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double h) {
  for (vector< vector<int> >::size_type i = 0; i < a.size(); i++) {
    r[i] = r[i] + v[i];
  }
}

void iteration_runge_kutta_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double h) {
  vector <vector2d> k1;
  vector <vector2d> k2;
  vector <vector2d> k3;
  vector <vector2d> k4;

  k1 = a;


  // Calc all the temporary values.
  vector <vector2d> rk1;
  for (vector< vector<int> >::size_type i = 0; i < a.size(); i++) {
    rk1[i] = r[i] + h * 1/2 * k1[i];
  }
  calc_accel_multiple(rk1, k2, m);

  vector <vector2d> rk2;
  for (vector< vector<int> >::size_type i = 0; i < a.size(); i++) {
    rk2[i] = r[i] + h * 1/2 * k2[i];
  }
  calc_accel_multiple(rk2, k3, m);

  vector <vector2d> rk3;
  for (vector< vector<int> >::size_type i = 0; i < a.size(); i++) {
    rk3[i] = r[i] + h * k3[i];
  }
  calc_accel_multiple(rk2, k4, m);

  for (vector< vector<int> >::size_type i = 0; i < a.size(); i++) {
    v[i] = v[i] + 1/6 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
  }
}
