#include "integration.h"

unsigned int ITEMS = 0;

void integration_start(listv2d& r, listv2d& v, listv2d& a, listdouble& m) {
  ITEMS = r.size();
  return;
}

void integration_euler(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, const double h, int ti) {
  for (int i = 0; i < ITEMS; i++) {
    // Calculate the next positions for r and v.
    r[i] = r[i] + h * v[i];
    v[i] = v[i] + h * a[i];
  }
}

void integration_heun(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, int ti) {
  listv2d r1(ITEMS);
  listv2d v1(ITEMS);
  listv2d a1(ITEMS);

  // Die Beschleunigung wurde schon für die aktuellen r berechnet
  // => Berechne schätzwerte
  for (int i = 0; i < ITEMS; i++) {
    // Calculate the next positions for r and v.
    r1[i] = r[i] + h * v[i];
    v1[i] = v[i] + h * a[i];
  }

  calc_accel_multiple(r1, a1, m);

  // Mit den neuen positionen/geschwindigkeiten kann man neue beschleunigungen ausrechnen
  // und damit wieder den endwert von heun.
  for (int i = 0; i < ITEMS; i++) {
    r[i] = r[i] + 0.5 * h * (v[i] + v1[i]);
    v[i] = v[i] + 0.5 * h * (a[i] + a1[i]);
  }
}

void integration_rk4(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, const double h, int ti) {
  listv2d r1(ITEMS);
  listv2d r2(ITEMS);
  listv2d r3(ITEMS);
  listv2d r4(ITEMS);

  listv2d v2(ITEMS);
  listv2d v3(ITEMS);
  listv2d v4(ITEMS);

  listv2d a2(ITEMS);
  listv2d a3(ITEMS);
  listv2d a4(ITEMS);

  for (int i = 0; i < ITEMS; i++) {
    r2[i] = r[i] + 0.5 * h * v[i];
    v2[i] = v[i] + 0.5 * h * a[i];
  }

  calc_accel_multiple(r2, a2, m);

  for (int i = 0; i < ITEMS; i++) {
    r3[i] = r[i] + 0.5 * h * v2[i];
    v3[i] = v[i] + 0.5 * h * a2[i];
  }
  calc_accel_multiple(r3, a3, m);

  for (int i = 0; i < ITEMS; i++) {
    r4[i] = r[i] + h * v3[i];
    v4[i] = v[i] + h * a3[i];
  }
  calc_accel_multiple(r4, a4, m);

  for (int i = 0; i < ITEMS; i++) {
    r[i] = r[i] + h/6.0 * (v[i] + 2.0 * v2[i] + 2.0 * v3[i] + v4[i]);
    v[i] = v[i] + h/6.0 * (a[i] + 2.0 * a2[i] + 2.0 * a3[i] + a4[i]);
  }
}

void integration_leap_frog(listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, int ti) {
  listv2d v1(ITEMS);

  // Store the previous accellerations so they don't have to be calculcated again
  static listv2d previous_accel;
  if (previous_accel.size() == 0) {
    for (int i = 0; i < ITEMS; i++) {
      previous_accel.push_back(calc_accel(r, m, i));
    }
  }

  for (int i = 0; i < ITEMS; i++) {
    // Use previous calculated f(t) for the new speed.
    v1[i] = v[i] + 0.5 * h * previous_accel[i];
    r[i] = r[i] + h * v1[i];

    //Calculate f(t+1) for the new speed.
    previous_accel[i] = calc_accel(r, m, i);
    v[i] = v1[i] + 0.5 * h * previous_accel[i];
  }
}


/**
 * Calculate the accelleration of one body.
 */
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

/**
 * Calculate the accelleration of all bodies.
 */
void calc_accel_multiple(const listv2d& r, listv2d& a, const vector<double>&m) {
  for (vector< vector<int> >::size_type i = 0; i < ITEMS; i++) {
    a[i] = calc_accel(r, m, i);
  }
}