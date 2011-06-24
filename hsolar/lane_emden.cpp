#include "integrator/integration.cpp"

double LANE_EMDEN_N = 3.0;

listDouble lane_emden_solve(double n, double hz, double h) {
  LANE_EMDEN_N = n;

  // The 0 value is the z, the 1 is the w and the 2 is the dwdz
  vector< listDouble > y_list;
  listDouble y_list_single(3);

  // Starting values.
  listDouble y(2), dydz;

  lane_emden_start(y);

  double z = 0.0;
  int count = 0;

  do {
    // Next step
    z += hz;
    // Calculate the new speed's.
    lane_emden_derivative(z, y, dydz);
    // Calculate the next values.
    integration_heun(y, dydz, z, h, lane_emden_derivative);

    // Write down the values.
    y_list_single[0] = z;
    y_list_single[1] = y[0];
    y_list_single[2] = y[1];
    y_list.push_back(y_list_single);

    count++;
  }
  while (
    // Stop if the function is < 0 the first time.
    y[0] <= 0.0 || count < 100000000);

  return y_list;
}

void lane_emden_derivative(const double x, const listDouble& y, listDouble& dyxy_out) {
  dyxy_out.push_back(y[1]);
  dyxy_out.push_back(- pow(y[0], LANE_EMDEN_N) - 2/x * y[1]);
}

void lane_emden_start(listDouble& y) {
  y[0] = 1.0;
  y[1] = 0.0;
}
