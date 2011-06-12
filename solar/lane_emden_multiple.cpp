#include "integrator/integration.cpp"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include "lane_emden.cpp"


int main(int argc, char **argv) {

  int n_steps = 10;
  double n = 0.0;
  do {
    n += 5.0/n_steps;

    listDouble lane_emden_output;
    lane_emden_output = lane_emden_solve(n);
    cout << n << " " << lane_emden_output[0] << " " << lane_emden_output[1] << endl;
  }
  while (n <= 5.0);

  return 0;
}
