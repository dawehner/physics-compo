#include "lane_emden.cpp"

#include "hsolar.h"

void hsolar_solve(double t1, double dt, double n) {

  int cell_n = 200;
  // Step one.
  vector< listDouble > y_list = lane_emden_solve(n, 0.0001, 0.0001);

  double gamma = (1.0 + n) / n;

  // +2 is there because of the ghost cells.
  listDouble rho(y_list.size() + 2);
  listDouble u(y_list.size() + 2);
  double rho_crit = 1.0;
  double z = 0.0;
  double K = 4.0 * M_PI / (n + 1.0);

  // Calculate the rho for the start values.
  hsolar_grid(cell_n, n, y_list, rho, u);
}

void hsolar_grid(const int N, const double n, const vector< listDouble >& y_list, listDouble& rho, listDouble u) {
  double z_max = y_list[y_list.size() - 1][0];
  double rho_crit = 1.0;

  double z_wanted = 0.0;
  double z_wanted_size = 0.0;
  int z_low, z_high = 0;
  double z_size = 0.0;

  double w_wanted = 0.0;
  for (int i = 0; i < N; i++) {

    // The size of a step we want.
    z_wanted_size = z_max / N;

    // The position on which we want the value.
    z_wanted = i * z_wanted;

    // The size of a step we calculated.
    z_size = z_max / y_list.size();

    // Calculate the wanted value of w based on a linear approx.
    z_low = floor(z_wanted / z_size);
    z_high = ceil(z_wanted / z_size);

    w_wanted = ((y_list[z_high][1] - y_list[z_low][1]) / (z_size)) * (z_wanted - z_low) + y_list[z_low][1];
    // Calculate the rho on the position.
    rho[i + 1] = rho_crit * pow(w_wanted, n);

    // Set the start values of the u's.
    u[i + 1] = 0.0;
  }
}