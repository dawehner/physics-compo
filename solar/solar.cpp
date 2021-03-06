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
// gravitaiton const [erg/cm]
const double GRAVITATION_CONST = 6.67384E-8;
// gas constant [erg K^-1 mol^-1]
const double GAS_CONST = 8.314472E7;

int main(int argc, char **argv) {  int c = 0;
  double mass = SOLAR_MASS;
  double radius = SOLAR_RADIUS;
  double GRAVITATION_CONST = 6.67384E-8;
  double mu = 0.0;

  string n_output;
  while ((c = getopt(argc, argv, ":n:o:r:m:g:u:")) != -1) {
    switch (c) {
      case 'n':
        LANE_EMDEN_N = atof(optarg);
        break;
      case 'm':
        mass = atof(optarg);
        break;
      case 'r':
        radius = atof(optarg);
        break;
      case 'g':
        GRAVITATION_CONST = atof(optarg);
        break;
      case 'o':
        n_output = optarg;
        break;
      case 'u':
        mu = atof(optarg);
        break;
    }
  }

  // Generate basic values for the star.
  double rho_middle = 3.0 * mass / (4.0 * M_PI * pow(radius, 3.0));
  double z_n = 0.0;
  double w_n = 0.0;
  double dwdz_n = 0.0;
  bool null_set = false;
  double A = 0.0;
  double K = 0.0;

  listDouble y(2), y_out(2), y_file(3);
  lane_emden_start(y);

  // Start values for ODE
  double h = 0.0001;
  double hx  = 0.0001;

  double x = 0.0;
  int count = 0;
  vector< vector<double> > y_list;

  // Calculate the solutions for lane-emden.
  do {
    x += hx;
    listDouble dydx;
    derivative(x, y, dydx);
    integration_heun(y, dydx, x, h, y_out, derivative);

    y_file[0] = y_out[0];
    y_file[1] = y_out[1];
    y_file[2] = x;

    // A single entry of y_list is a vector with 0:w 1:dw/dz 2: z
    y_list.push_back(y_file);
    if (!null_set && y_out[0] <= 0.0) {
      derivative(x, y_out, dydx);
      z_n = x;
      w_n = y_out[0];
      dwdz_n = y[1];

      // Don't set the values again.
      null_set = true;
    }

    y = y_out;

    count++;
  }
  while (x < 20.0 && count < 1000000);

  // Calculate some needed values.
  double rho_core = rho_middle / (-3 * dwdz_n / z_n);
  A = z_n / radius;
  K = 4 * M_PI * GRAVITATION_CONST * pow(rho_core, (LANE_EMDEN_N - 1.0) / LANE_EMDEN_N) / ((LANE_EMDEN_N + 1.0) * pow(A, 2.0));
  double mass_total = 4 * M_PI * rho_core * pow(radius, 3) * (- dwdz_n/z_n );
  double masss_total_dimless = 4 * M_PI * rho_core * pow(z_n, 3) * (- dwdz_n/z_n );
  double p_core = K * pow(rho_core, (LANE_EMDEN_N + 1) / LANE_EMDEN_N);
  double temp_core =  p_core * mu / ( rho_core * GAS_CONST);

  // Write down the values.
  ofstream output_file;

  string output_filename = "lane_emden_";
  if (n_output.empty()) {

    std::ostringstream sstream;
    sstream << LANE_EMDEN_N;
    std::string n = sstream.str();
    n_output = n;
  }
  else {
    output_filename = output_filename.append(n_output).append(".dat");
  }

  output_file.open(output_filename.c_str());

  double w = 0.0;
  double dwdz = 0.0;
  double r = 0.0;
  double rho = 0.0;
  double z = 0.0;
  double p = 0.0;

  // Write down the lane-emden data.
  // The conten of lane_emden_n.dat is:
  // - z
  // - w
  // - dwdz
  // - r
  // - rho
  // - p

  for (unsigned int i = 0; i < y_list.size(); i++) {
    // Only calculate values until the edge of the star.
    if (z > z_n) {
      break;
    }
    w = y_list[i][0];
    dwdz = y_list[i][1];
    z = y_list[i][2];

    r = z / A;
    rho = rho_core * pow(w, LANE_EMDEN_N);
    p = K * pow(rho, (LANE_EMDEN_N + 1) / LANE_EMDEN_N);

    // Write down the values.
    output_file << scientific << z << "\t" << w << "\t" << dwdz << "\t";
    output_file << r << "\t" << rho << "\t" << p << endl;
  }
  output_file.close();

  // Write down the constant solar data.
  // The content of solar_n.dat is:
  // - rho_crit
  // - rho_middle
  // - K
  // - A
  // - mass
  // - radius
  // - mass_total
  string output_solar_filename = "solar_";
  output_solar_filename.append(n_output);
  output_solar_filename.append(".dat");
  ofstream output_solar_file;
  output_solar_file.open(output_solar_filename.c_str());
  output_solar_file << rho_core << "\t" << rho_middle << "\t"
  << K << "\t" << A << "\t" <<
  mass << "\t" << radius << "\t" <<
  z_n << "\t" << mass_total << "\t" <<
  temp_core << "\t" << p_core << "\t" <<
  masss_total_dimless << endl;

  output_file.close();

  return 0;
}