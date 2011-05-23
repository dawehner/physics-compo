#include "iteration.h"

unsigned int count_item = 0;

void iteration_start(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m) {
  count_item = r.size();
}

void iteration_next(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h,
  void (*method_r) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h),
  void (*method_v) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h)) {


  method_r(r, v, a, m, h);
  method_v(r, v, a, m, h);

  // Recall all a's.
  calc_accel_multiple(r, a, m);

}


inline vector2d calc_accel(const vector<vector2d>& r, const vector<double>& m, const unsigned j) {
  vector2d a;
  a.x = 0.0;
  a.y = 0.0;
  vector2d connection;
  connection.x = 0.0;
  connection.y = 0.0;
  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    if (i != j) {
      connection = r[i] - r[j];
      a = a + (m[i] / pow(norm(connection), 3)) * (connection);
    }
  }

//   a *= G;
//   a *= -1;
  return a;
}


void iteration_euler_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h) {
  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    // Calculate the next value for r.
    r[i] = r[i] + h * v[i];
  }
}

void iteration_euler_v (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, double h) {
  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    // Calculate the next value for v.
    v[i] = v[i] + h * a[i];
  }
}

void iteration_heun_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double h) {
//   vector <vector2d> r_tmp_next = r;
  iteration_euler_r(r, v, a, m, h);

//   vector <vector2d> v_tmp_next = v;
//   iteration_euler_v(r_tmp_next, v_tmp_next, a, m, h);
//   for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
//     cout << v_tmp_next << endl;
//     r[i] = r[i] + (h/2) * (v[i] + v_tmp_next[i]);
//   }
}

void iteration_heun_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double h) {
  vector <vector2d> v_tmp_next = v;
  iteration_euler_v(r, v_tmp_next, a, m, h);

  vector <vector2d> r_tmp_next = v;
  iteration_euler_r(r_tmp_next, v_tmp_next, a, m, h);

  vector2d ai_tmp_next;
  ai_tmp_next.x = 0.0;
  ai_tmp_next.y = 0.0;
  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    ai_tmp_next = calc_accel(r_tmp_next, m, i);
    v[i] = v[i] + (h/2) * (a[i] + ai_tmp_next);
  }
}

void calc_accel_multiple(const vector< vector2d>& r, vector< vector2d>& a, const vector<double>&m) {
  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    a[i] = calc_accel(r, m, i);
  }
}

void iteration_runge_kutta_r(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double h) {
  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    r[i] = r[i] + v[i];
  }
}

void iteration_runge_kutta_v(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector<double>& m, double h) {
  vector <vector2d> k1(count_item);
  vector <vector2d> k2(count_item);
  vector <vector2d> k3(count_item);
  vector <vector2d> k4(count_item);

  k1 = a;

  // Calc all the temporary values.
  vector <vector2d> rk1(r.size());
  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    rk1[i] = r[i] + h * 1/2 * k1[i];
  }
  calc_accel_multiple(rk1, k2, m);

  vector <vector2d> rk2(r.size());
  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    rk2[i] = r[i] + h/2 * k2[i];
  }
  calc_accel_multiple(rk2, k3, m);

  vector <vector2d> rk3(r.size());
  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    rk3[i] = r[i] + h * k3[i];
  }
  calc_accel_multiple(rk2, k4, m);

  for (vector< vector<int> >::size_type i = 0; i < count_item; i++) {
    v[i] = v[i] + 1/6 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
  }
}
