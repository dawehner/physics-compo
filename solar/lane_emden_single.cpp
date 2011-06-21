#include "integrator/integration.cpp"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include "lane_emden.cpp"
#include <fstream>
#include <sstream>


int main(int argc, char **argv) {
  int c = 0;
  while ((c = getopt(argc, argv, ":n:")) != -1) {
    switch (c) {
      case 'n':
        LANE_EMDEN_N = atof(optarg);
        break;
    }
  }

  listDouble y(2), y_out(2);
  lane_emden_start(y);

  double h = 0.0001;
  double hx  = 0.0001;

  double x = 0.0;
  int count = 0;

  ofstream output_file;
  string output_filename = "lane_emden_";

  std::ostringstream sstream;
  sstream << LANE_EMDEN_N;
  std::string n = sstream.str();

  output_filename.append(n);
  output_filename.append(".dat");

  output_file.open(output_filename.c_str());

  do {
    x += hx;
    listDouble dyxy;
    derivative(x, y, dyxy);
    integration_heun(y, dyxy, x, h, y_out, derivative);
    y = y_out;
    output_file << x << "\t" << y[0] << "\t" << y[1] << std::endl;
    count++;
  }
  while (x < 20.0 && count < 1000000);
  output_file.close();

  return 0;
}
