#ifndef HSOLAR_CPP
#define HSOLAR_CPP

#include "lane_emden.cpp"

#include "hsolar.h"

#include <iostream>
using namespace std;

void hsolar_solve(double t1, double dt, double n) {

  int cell_n = 10;
  // Step one.
  vector< listDouble > y_list = lane_emden_solve(n, 0.0001, 0.0001);
//   for (int i = 0; i < y_list.size(); i++) {
//     for (int j = 0; j < y_list[i].size(); j++) {
//       cout << y_list[i][j] << "\t";
//     }
//     cout << endl;
//   }

  double gamma = (1.0 + n) / n;

  // +2 is there because of the ghost cells.
  listDouble rho(cell_n + 2);
  listDouble u(cell_n + 2);
//   double rho_crit = 1.0;
//   double z = 0.0;
  double K = 4.0 * M_PI / (n + 1.0);
  double z_max = y_list[y_list.size() - 1][0];
  double z_size = z_max / y_list.size();

  // Calculate the rho for the start values.
  hsolar_grid(cell_n, n, y_list, rho, u);

  double t = 0.0;
  while (t < t1) {
    hsolar_single_timestamp(rho, u, dt, z_max, z_size, cell_n, gamma, K);
    cout << "#################################################" << endl;

    for (int i = 0; i < rho.size(); i++) {
      cout << rho[i] << endl;
    }

    t += dt;
  }


  return;
}

void hsolar_single_timestamp(listDouble& rho, listDouble& u, const double dt,
  const double z_max, const double z_size, const int N, const double gamma, const double K) {
  int size = u.size();

  // Calculate the new densities.
  listDouble rho_pre = rho;
  for (int i = 1; i < size - 1; i++) {
    double r_i_a = (i - 0.5) * z_size;
    double r_i1_a = (i + 0.5) * z_size;
    double vol_cell = (4.0 * M_PI / 3.0) * (pow(r_i1_a, 3.0) + pow(r_i_a, 3.0));

    double s_i_a = 4 * M_PI * pow(r_i_a, 2.0);
    double s_i1_a = 4 * M_PI * pow(r_i1_a, 2.0);

    double rho_i_s = u[i] > 0.0 ? rho[i - 1] : rho[i];
    double rho_i1_s = u[i + 1] > 0.0 ? rho[i ] : rho[i + 1];
    double f_i_m = u[i] * rho_i_s;
    double f_i1_m = u[i + 1] * rho_i1_s;

    rho[i] = rho[i] - (dt / vol_cell) * (s_i1_a * f_i1_m - s_i_a * f_i_m);
  }

  // Set ghost cells
  hsolar_ghostcells_rho(rho);

  // Calculate the druck for all positions.
  listDouble p(rho.size());
  for (int i = 0; i < size; i++) {
    p[i] = K * pow(rho[i], gamma / (gamma - 1.0));
  }

  // Calculate the masses for all positions.
  listDouble m(rho.size());
  double m_help = 0.0;
  for (int i = 1; i < size - 1; i++) {
    m_help += z_size * rho[i];
    m[i] = m_help;
  }

  // Calculate the new speeds.


  listDouble w(u.size());
  listDouble u_next(u.size());
  for (int i = 1; i < size - 1; i++) {
    double rho_pre_m = 0.5 * (rho_pre[i] + rho_pre[i - 1]);
    w[i] = u[i] * rho_pre_m;
  }

  for (int i = 1; i < size - 1; i++) {
    double rho_pre_m = 0.5 * (rho_pre[i] + rho_pre[i - 1]);
    double rho_next1_m = 0.5 * (rho_pre[i + 1] + rho_pre[i]);

    // @todo: Check the position of r_i_b and r_i1_b.
    double r_i_b = (i) * z_size;
    double r_i1_b = (i + 1) * z_size;
    double vol_cell = (4.0 * M_PI / 3.0) * (pow(r_i1_b, 3.0) + pow(r_i_b, 3.0));
    double s_i_b = 4 * M_PI * pow(r_i_b, 2.0);
    double s_i1_b = 4 * M_PI * pow(r_i1_b, 2.0);

    double u_i_m = 0.5 * (u[i] + u[i + 1]);
    double u_1i_m = 0.5 * (u[i] + u[i - 1]);
    double w_i_s = u_i_m > 0.0 ? w[i] : w[i + 1];
    double w_1i_s = u_1i_m > 0.0 ? w[i - 1] : w[i];

    double f_i = w_i_s * u_i_m;
    double f_1i = w_1i_s * u_1i_m;

    double w_temp = w[i] - (dt / vol_cell) * (s_i1_b * f_i - s_i_b * f_1i);
    double u_temp = w_temp / rho_next1_m;

    double r_i_a = (i + 0.5) * z_size;
    // Apply the forces.
    double fgrav = - m[i] / (pow(r_i_a, 2.0));
    u_next[i] = u_temp + dt * (fgrav -
      (1.0/rho_pre_m) * (p[i] - p[i - 1]) / (r_i_b - r_i1_b));
  }

  // Store the new speeds.
  u = u_next;
}

void hsolar_grid(const int N, const double n, const vector< listDouble >& y_list, listDouble& rho, listDouble u) {
  double z_max = y_list[y_list.size() - 1][0];
  double rho_crit = 1.0;

  double z_wanted = 0.0;
  int z_low, z_high = 0;
  // The size of a step we calculated.
  double z_size = z_max / y_list.size();
  // The size of a step we want.
  double z_wanted_size = z_max / N;

  double w_wanted = 0.0;
  for (int i = 0; i < N; i++) {
    // The position on which we want the value.
    z_wanted = i * z_wanted_size;

    // Calculate the wanted value of w based on a linear approx.
    z_low = floor(z_wanted / z_size);
    z_high = ceil(z_wanted / z_size);

    w_wanted = ((y_list[z_high][1] - y_list[z_low][1]) / (z_size)) * (z_wanted - z_low * z_size) + y_list[z_low][1];
    // Calculate the rho on the position.
    rho[i + 1] = rho_crit * pow(w_wanted, n);

    // Set the start values of the u's.
    u[i + 1] = 0.0;
  }

  // Set some start values.
  hsolar_ghostcells_rho(rho);
  u[0] = 0.0;
  u[u.size()] = 0.0;
}

void hsolar_ghostcells_rho(listDouble& rho) {
  rho[0] = rho[1];
  rho[rho.size()] = rho[rho.size() - 1];
}

#endif