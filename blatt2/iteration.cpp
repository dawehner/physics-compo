#include <cmath>
#include <vector>
#include "vector.cpp"
#include <iostream>

using namespace std;

const int ITERATION_EULER = 0;
const int ITERATION_HEUN = 1;
const int ITERATION_RUNGE_KUTTA = 2;

const double G = 1;

void iteration_next(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double tk, double h,
  void (*method_r) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double tk, double h),
  void (*method_v) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double tk, double h));

void iteration_euler_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double tk, double h);
void iteration_euler_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double tk, double h);
void iteration_heun_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double tk, double h);
void iteration_heun_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double tk, double h);
// void iteration_runge_kutta_r(vector<vector2d> r, vector<vector2d> v, vector<vector2d> a, vector<double>& m, double tk);
// void iteration_runge_kutta_v(vector<vector2d> r, vector<vector2d> v, vector<vector2d> a, vector<double>& m, double tk);

vector2d calc_accel(vector< vector2d >& r, std::vector< double >& m, unsigned int j);

void iteration_next(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double tk, double h,
  void (*method_r) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double tk, double h),
  void (*method_v) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double tk, double h)) {
  // First calc all new r's based on the given method.
  // @todo is this really a copy?
  vector< vector2d > rk = r;
  // Therefore it's important not to use the new r's for the calculation of the new v's.
  method_r(r, v, a, m, tk, h);

  // Then calc all new v's based on the given method.
  method_v(r, v, a, m, tk, h);

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


void iteration_euler_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double tk, double h) {
  for (vector< vector<int> >::size_type i = 0; i < r.size(); i++) {
    // Calculate the next value for r.
    r[i] = r[i] + h * v[i];
  }
}

void iteration_euler_v (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double tk, double h) {
  for (vector< vector<int> >::size_type i = 0; i < v.size(); i++) {
    // Calculate the next value for v.
    v[i] = v[i] + h * a[i];
  }
}

void iteration_heun_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double tk, double h) {
  vector <vector2d> r_tmp_next = r;
  iteration_euler_r(r_tmp_next, v, a, m, tk, h);
  vector <vector2d> v_tmp_next = v;
  iteration_heun_v(r_tmp_next, v_tmp_next, a, m ,tk, h);
  for (vector< vector<int> >::size_type i = 0; i < r.size(); i++) {
    r[i] = r[i] + (h/2) * (v[i] + v_tmp_next[i]);
  }
}

void iteration_heun_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double tk, double h) {
  vector <vector2d> v_tmp_next = v;
  iteration_euler_v(r, v_tmp_next, a, m, tk, h);
  vector <vector2d> r_tmp_next = v;
  iteration_euler_r(r_tmp_next, v_tmp_next, a, m, tk, h);

  vector2d ai_tmp_next;
  for (vector< vector<int> >::size_type i = 0; i < v.size(); i++) {
    ai_tmp_next = calc_accel(r_tmp_next, m, i);
    v[i] = v[i] + (h/2) * (a[i] + ai_tmp_next);
  }
}
