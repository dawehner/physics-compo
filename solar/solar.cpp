#include "integrator/integration.cpp"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include "lane_emden.cpp"
#include <fstream>
#include <sstream>

const double SOLAR_N = 3;
const double SOLAR_MASS = 1.989E33;
const double SOLAR_RADIUS = 6.96E10;
// gravitaiton const in erg/cm
const double GRAVITATION_CONST = 6.67384E-8;

int main(int argc, char **argv) {
  //. Setup initial values
  double n = SOLAR_N;
  double m = SOLAR_MASS;
  double r= SOLAR_RADIUS;

  int c = 0;
  while ((c = getopt(argc, argv, ":n:r:m")) != -1) {
    switch (c) {
      case 'n':
        n = atof(optarg);
        break;
      case 'm':
        m = atof(optarg);
        break;
      case 'r':
        r = atof(optarg);
        break;
    }
  }

  listDouble lane_emden_output = lane_emden_solve(n, 0.01, 0.01);
  double z_n = lane_emden_output[0];
  double zz_wz_n = lane_emden_output[1];

  double ro_middle = m / ( 4 * M_PI * pow(r, 3.0) / 3);
  // @see A20
  double ro_crit = ro_middle / ((3/pow(z_n, 3.0)) * zz_wz_n);

  // A can be used later for scaling.
  double A = z_n / r;

  //@see A9
  double K = M_PI * GRAVITATION_CONST / pow(A, 2.0)
    * pow(ro_crit, (n - 1) / n);


  ofstream output_file;

  std::ostringstream sstream;
  sstream << n;
  std::string n_str = sstream.str();

  string output_filename = "solar-" + n_str + ".dat";

  output_file.open(output_filename.c_str());
  output_file << ro_crit << "\t" << ro_middle << "\t" << K << "\t" << A << endl;
  output_file.close();

  return 0;
}