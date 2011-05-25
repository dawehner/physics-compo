#include "integration.h"

unsigned int ITEMS = 0;

void integration_start(listv2d& r, listv2d& v, listv2d& a, listdouble& m) {
  ITEMS = r.size();
  return;
}

void integration_euler(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, const double h) {
  for (int i = 0; i < ITEMS; i++) {
    // Calculate the next positions for r and v.
    r[i] = r[i] + h * v[i];
    v[i] = v[i] + h * a[i];
  }
}

void integration_heun(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h) {
  listv2d& r2 = r;
  listv2d& v2 = v;
  listv2d& a1 = a;

  // Die Beschleunigung wurde schon für die aktuellen r berechnet
  // => Berechne schätzwerte
  integration_euler(r2, v2, a, m, h);

  // Mit den neuen positionen/geschwindigkeiten kann man neue beschleunigungen ausrechnen
  // und damit wieder den endwert von heun.
  for (int i = 0; i < ITEMS; i++) {
    r[i] = r[i] + 0.5 * h * (v[i] + v2[i]);
    v[i] = v[i] + 0.5 * h * (a[i] + a1[i]);
  }
}

void integration_rk4(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, const double h) {
  listv2d r1 = r;
  listv2d r2 = r;
  listv2d r3 = r;
  listv2d r4 = r;

  listv2d v1 = v;
  listv2d v2 = v;
  listv2d v3 = v;
  listv2d v4 = v;

  listv2d a1 = a;
  listv2d a2 = a;
  listv2d a3 = a;
  listv2d a4 = a;

  for (int i = 0; i < ITEMS; i++) {
    r2[i] = r[i] + h * v1[i];
    v2[i] = v[i] + h * a1[i];
  }

  calc_accel_multiple(r2, a2, m);

  for (int i = 0; i < ITEMS; i++) {
    r3[i] = r[i] + h * v2[i];
    v3[i] = v[i] + h * a2[i];
  }
  calc_accel_multiple(r3, a3, m);

  for (int i = 0; i < ITEMS; i++) {
    r4[i] = r[i] + h * v3[i];
    v4[i] = v[i] + h * a3[i];
  }
  calc_accel_multiple(r4, a4, m);

  for (int i = 0; i < ITEMS; i++) {
    r[i] = r[i] + h/6 * (v1[i] + 2 * v2[i] + 2 * v3[i] + v4[i]);
    v[i] = v[i] + h/6 * (a1[i] + 2 * a2[i] + 2 * a3[i] + a4[i]);
  }
}


inline vector2d calc_accel(const listv2d& r, const listdouble m, const unsigned int j) {
  vector2d a;
  a.x = 0.0;
  a.y = 0.0;
  vector2d connection;
  connection.x = 0.0;
  connection.y = 0.0;
  for (int i = 0; i < ITEMS; i++) {
    if (i != j) {
      connection = r[i] - r[j];
      a = a + (m[i] / pow(norm(connection), 3)) * (connection);
    }
  }

//   a *= G;
//   a *= -1;
  return a;
}

void calc_accel_multiple(const listv2d& r, listv2d& a, const vector<double>&m) {
  for (vector< vector<int> >::size_type i = 0; i < ITEMS; i++) {
    a[i] = calc_accel(r, m, i);
  }
}