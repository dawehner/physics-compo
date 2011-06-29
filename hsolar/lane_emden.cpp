#ifndef LANE_EMDEN_CPP
#define LANE_EMDEN_CPP

#include "integrator/integration.cpp"
#include "lane_emden.h"

#include <iostream>
using namespace std;

double LANE_EMDEN_N = 3.0;

void lane_emden_solve(double n, double hz, double h, vector< vector<double> >& y_list) {
  LANE_EMDEN_N = n;

  // The 0 value is the z, the 1 is the w and the 2 is the dwdz
  listDouble y_list_single(3);

  // Starting values.
  listDouble y(2), y_out(2), dydz;
  y[0] = 1.0;
  y[1] = 0.0;
  y_out = y;

  lane_emden_start(y);

  double z = 0.0;
  int count = 0;

  do {
    y = y_out;
    // Next step
    z += hz;
    // Calculate the new speed's.
    lane_emden_derivative(z, y, dydz);
    // Calculate the next values.
    integration_heun(y, dydz, z, h, y_out, lane_emden_derivative);

    // Write down the values.
    y_list_single[0] = z;
    y_list_single[1] = y_out[0];
    y_list_single[2] = y_out[1];
    y_list.push_back(y_list_single);

    count++;
//     cout << y_out[0] << endl;
  }
  while (
    // Stop if the function is < 0 the first time.
    y_out[0] >= 0.0 && count < 100000000);
}

void lane_emden_derivative(const double x, listDouble& y, listDouble& dyxy_out) {
  dyxy_out.push_back(y[1]);
  dyxy_out.push_back(- pow(y[0], LANE_EMDEN_N) - 2/x * y[1]);
}

void lane_emden_start(listDouble& y) {
  y[0] = 1.0;
  y[1] = 0.0;
}

#endif