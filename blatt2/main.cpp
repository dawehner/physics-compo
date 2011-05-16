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
void output_converseved_quantities(double E1, double L1, ofstream& output_file_energy, ofstream& output_file_angular_momentum);
void output_orbital_parameters(double a1, double e1, ofstream& output_file_a, ofstream& output_file_e);

int main(int argc, char **argv) {
  int c;
  void (*method_r) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, double h);
  void (*method_v) (vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, double h);

  vector< vector2d > r;
  vector< vector2d > v;
  vector< vector2d > a;
  vector< double > m;
  double tk;
  double h;
  int P_count = 10;

  // Some example content.
  h = 0.1;
  tk = 0;

  vector2d r1;
  r1.x = 0.0;
  r1.y = 0.0;
  vector2d r2;
  r2.x = 0.0;
  r2.y = 10.0;
  vector2d r3;
  r3.x = 0.0;
  r3.y = -5.0;
  r.push_back(r1);
  r.push_back(r2);
//   r.push_back(r3);

  vector2d v1;
  vector2d v2;
  v2.x = 1;
  vector2d v3;
  v3.x = -0.5;
  v.push_back(v1);
  v.push_back(v2);
//   v.push_back(v3);

  vector2d a1, a2, a3;
  a.push_back(a1);
  a.push_back(a2);
//   a.push_back(a3);

  m.push_back(1);
  m.push_back(1e-3);
//   m.push_back(1e-6);


  int iteration = ITERATION_HEUN;
  string filename = "output";
  bool write_to_files = false;

  // Load data from input
  while ((c = getopt(argc, argv, ":i:o:h:c:")) != -1) {
    switch (c) {
      // Set interation method
      case 'i':
        iteration = atof(optarg);
      // set excent value
        break;
      case 'o':
        filename = optarg;
        write_to_files = true;
        break;
      case 'h':
        h = atof(optarg);
        break;
      case 'c':
        P_count = atof(optarg);
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
      method_r = iteration_runge_kutta_r;;
      method_v = iteration_runge_kutta_v;
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

  iteration_start(r, v, a, m);

  // Here comes the main loop
  int count = 0;
  int t_max = calc_t_max(P, P_count, 100);
  cout << t_max << endl;

  while (count < t_max) {
    iteration_next(r, v, a, m, h, method_r, method_v);
    count++;

    if (write_to_files) {
      output_movement_data(r, v, a, m, output_file);

      // Calc all needed variab10les and output them into files.
      vector2d r_rel = r[1] - r[0];
      vector2d v_rel = v[1] - v[0];

      double great_half_axis = calc_great_half_axis(r_rel, v_rel, m);
      double excentric = calc_excentric(r_rel, v_rel, m, great_half_axis);
      double energy = calc_energy(m, great_half_axis);
      double angular_momentum = calc_angular_momentum(m, great_half_axis, excentric);

      output_converseved_quantities(energy, angular_momentum, output_file_energy, output_file_angular_momentum);
      output_orbital_parameters(great_half_axis, excentric, output_file_a, output_file_e);
    }
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
void output_converseved_quantities(double E1, double L1, ofstream& output_file_energy, ofstream& output_file_angular_momentum) {
  if (output_file_energy.is_open()) {
    output_file_energy << E1 << endl;
  }
  if (output_file_angular_momentum.is_open()) {
    output_file_angular_momentum << L1 << endl;
  }
}


/**
 * Output the excentric/great half axis to a file.
 */
void output_orbital_parameters(double a1, double e1, ofstream& output_file_a, ofstream& output_file_e) {
  if (output_file_a.is_open()) {
    output_file_a << a1 << endl;
  }

  if (output_file_e.is_open()) {
    output_file_e << e1 << endl;
  }
}
