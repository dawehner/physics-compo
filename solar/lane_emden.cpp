#include "integrator/integration.cpp"
#include <cmath>
#include <iostream>
#include <stdlib.h>


using namespace std;


double LANE_EMDEN_N = 0.0;

void derivative(const double x, listDouble& y, listDouble& dyxy_out);
void lane_emden_start(listDouble& y);

/**
 * Solves lane emden for a certain n and return the results:
 *   - z_n
 *   - z^2 ...
 */
listDouble lane_emden_solve(double n, const double h = 0.01, const double hx = 0.01);

void derivative(const double x, listDouble& y, listDouble& dyxy_out) {
  dyxy_out.push_back(y[1]);
  dyxy_out.push_back(- pow(y[0], LANE_EMDEN_N) - 2/x * y[1]);
}

void lane_emden_start(listDouble& y) {
  y[0] = 1.0;
  y[1] = 0.0;
}


listDouble lane_emden_solve(double n, const double h, const double hx) {
  /**
   * @todo: Figure out a way to work around the global, it sucks!.
   */
  LANE_EMDEN_N = n;
  // Copy 
  listDouble y(2), y_out(2);
  lane_emden_start(y);

  double x = 0.0;
  int count = 0;
  do {
    x += hx;
    listDouble dyxy;
    derivative(x, y, dyxy);
    integration_rk4(y, dyxy, x, h, y_out, derivative);
    y = y_out;
    count++;
  }
  // Break once the value get's lower 0 or there is no solution.
  while (y_out[0] > 0.0 && count < 1000000);

  listDouble output;

  double z_n = x;
  double zz_wz_n = - pow(x, 2.0) * y_out[1];
  output.push_back(z_n);
  output.push_back(zz_wz_n);

  return output;
}