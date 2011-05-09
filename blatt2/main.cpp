#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "iteration.cpp"
#include <fstream>
#include "quantities.cpp"
#include <vector>

using namespace std;

ofstream emptystream;

void output_movement_data(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, ofstream& output_file);
void output_converseved_quantities(double E1, double E2, double L1, double L2, ofstream& output_file_energy, ofstream& output_file_angular_momentum);
void output_orbital_parameters(double a1, double a2, double e1, double e2, ofstream& output_file_a, ofstream& output_file_e);

int main(int argc, char **argv) {
  int c;
  void (*method_r) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, double tk, double h);
  void (*method_v) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, double tk, double h);

  vector< vector2d > r;
  vector< vector2d > v;
  vector< vector2d > a;
  vector< double > m;
  double tk;
  double h;

  // Some example content.
  h = 0.1;
  tk = 0;

  vector2d r1(0.0, 0.0);
  vector2d r2(0.0, 10.0);
  vector2d r3(0.0, -5.0);
  r.push_back(r1);
  r.push_back(r2);
//   r.push_back(r3);

  vector2d v1(0, 0);
  vector2d v2(1, 0);
  vector2d v3(-0.5, 0);
  v.push_back(v1);
  v.push_back(v2);
//   v.push_back(v3);

  vector2d a1(0.0, 0.0);
  vector2d a2(0.0, 0.0);
  vector2d a3(0.0, 0.0);
  a.push_back(a1);
  a.push_back(a2);
//   a.push_back(a3);

  m.push_back(1);
  m.push_back(1e-3);
//   m.push_back(1e-6);


  int iteration = ITERATION_HEUN;
  string filename = "output";

  // Load data from input
  while ((c = getopt(argc, argv, ":i:o:h:")) != -1) {
    switch (c) {
      // Set interation method
      case 'i':
        iteration = atof(optarg);
      // set excent value
        break;
      case 'o':
        filename = optarg;
        break;
      case 'h':
        h = atof(optarg);
        break;
    }
  }


  switch (iteration) {
    case ITERATION_EULER:
      method_r = iteration_euler_r;
      method_v = iteration_euler_v;
    break;
    case ITERATION_HEUN:
      method_r = iteration_heun_r;
      method_v = iteration_heun_v;
    break;
    case ITERATION_RUNGE_KUTTA:
      // @todo: IMplement it.
      break;
  }

  // Generate a lot of filestreams for the different kind of output.
//   vector< ofstream* > files;

  ofstream output_file;
  string output_filename = filename + ".dat";
  output_file.open(output_filename.c_str());
//   files.push_back(output_file);


  ofstream output_file_energy;
  output_filename = filename + "-energy.dat";
  output_file_energy.open(output_filename.c_str());
//   files.push_back(output_file_energy);


  ofstream output_file_angular_momentum;
  output_filename = filename + "-momentum.dat";
  output_file_angular_momentum.open(output_filename.c_str());
//   files.push_back(output_file_angular_momentum);


  ofstream output_file_a;
  output_filename = filename + "-axis.dat";
  output_file_a.open(output_filename.c_str());
//   files.push_back(output_file_a);

  ofstream output_file_e;
  output_filename = filename + "-excentric.dat";
  output_file_e.open(output_filename.c_str());
//   files.push_back(output_file_e);

  if (!output_file.is_open()) {
    cout << "Couldn't open file to write." << endl;
    return EXIT_FAILURE;
  }

  double P = calc_periode(m);

  // Here comes the main loop
  int count = 0;
  int t_max = calc_t_max(P, 10, 100);
  cout << t_max << endl;

  while (count < t_max) {
    iteration_next(r, v, a, m, tk, h, method_r, method_v);
    count++;
    output_movement_data(r, v, a, m, output_file);


    // Calc all needed variables and output them into files.
    double great_half_axis1 = calc_great_half_axis(r[0], v[0], m);
    double great_half_axis2 = calc_great_half_axis(r[1], v[2], m);
    double excentric1 = calc_excentric(r[0], v[0], m, great_half_axis1);
    double excentric2 = calc_excentric(r[1], v[1], m, great_half_axis2);
    double energy1 = calc_energy(m, great_half_axis1);
    double energy2 = calc_energy(m, great_half_axis2);
    double angular_momentum1 = calc_angular_momentum(m, great_half_axis1, excentric1);
    double angular_momentum2 = calc_angular_momentum(m, great_half_axis2, excentric2);

    output_converseved_quantities(energy1, energy2, angular_momentum1, angular_momentum2, output_file_energy, output_file_angular_momentum);
    output_orbital_parameters(great_half_axis1, great_half_axis2, excentric1, excentric2, output_file_a, output_file_e);
  }

  if (output_file.is_open()) {
    output_file.close();
  }
    if (output_file_energy.is_open()) {
    output_file_energy.close();
  }
    if (output_file_angular_momentum.is_open()) {
    output_file_angular_momentum.close();
  }
    if (output_file_a.is_open()) {
    output_file_a.close();
  }
    if (output_file_e.is_open()) {
    output_file_e.close();
  }


  return 0;
}
// const double G = 6.6726e-11;

/**
 * Output the movement of the bodies itself to a file.
 */
void output_movement_data(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, ofstream &output_file = emptystream) {
  // headers
//   cout << "x \t y \t vx \t vy \t ax \t ay \t m" << endl;
  if (output_file.is_open()) {
    for (vector< vector<int> >::size_type i = 0; i < r.size(); i++) {
      output_file << r[i].x << "\t";
      output_file << r[i].y << "\t";
      output_file << v[i].x << "\t";
      output_file << v[i].y << "\t";
      output_file << a[i].x << "\t";
      output_file << a[i].y << "\t";
      output_file << m[i];
      output_file << endl;
    }
  }
}

/**
 * Output the energy/angular momentum.
 */
void output_converseved_quantities(double E1, double E2, double L1, double L2, ofstream& output_file_energy, ofstream& output_file_angular_momentum) {
  if (output_file_energy.is_open()) {
    output_file_energy << E1 + E2 << endl;
  }
  if (output_file_angular_momentum.is_open()) {
    output_file_angular_momentum << L1 + L2 << endl;
  }
}


/**
 * Output the excentric/great half axis to a file.
 */
void output_orbital_parameters(double a1, double a2, double e1, double e2, ofstream& output_file_a, ofstream& output_file_e) {
  if (output_file_a.is_open()) {
    output_file_a << a1 + a2 << endl;
  }

  if (output_file_e.is_open()) {
    output_file_e << e1 + e2 << endl;
  }
}
