#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <istream>
#include <vector>
#include <fstream>

#include "integration.cpp"
#include "quantities.cpp"
#include "string_helper.cpp"

using namespace std;

ofstream emptystream;

void output_movement_data(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, ofstream& output_file);
void output_converseved_quantities(double E1, double L1, ofstream& output_file_energy, ofstream& output_file_angular_momentum);
void output_orbital_parameters(double a1, double e1, ofstream& output_file_a, ofstream& output_file_e);
void init_values_from_file(listv2d& r, listv2d& v, listdouble& m, string input_filename);
void init_values_default(listv2d& r, listv2d& v, listv2d& a, listdouble& m);


int main(int argc, char **argv) {
  int c;
  void (*integration_method) (listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h);

  int iteration = INTEGRATION_RUNGE_KUTTA;
  string filename = "output";
  string input_filename = "input.dat";
  bool write_to_files = true;
  bool read_from_file = false;

  double h;
  int P_count = 10;

  // Load data from input
  while ((c = getopt(argc, argv, ":i:o:h:c:f:")) != -1) {
    switch (c) {
      // Set interation method
      case 'i':
        iteration = atof(optarg);
      // set excent value
        break;
      // Set the output filenames
      case 'o':
        filename = optarg;
        write_to_files = true;
        break;
      // Set stepsize
      case 'h':
        h = atof(optarg);
        break;
      // Set the amount of periods
      case 'c':
        P_count = atof(optarg);
      // Set the input filenames.
      case 'f':
        read_from_file = true;
        input_filename = optarg;
        break;
    }
  }


  switch (iteration) {
    case INTEGRATION_EULER:
      integration_method = integration_euler;
      break;
    case INTEGRATION_HEUN:
      integration_method = integration_heun;
      break;
    case INTEGRATION_RUNGE_KUTTA:
      integration_method = integration_rk4;
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


  listv2d r, v, a;
  listdouble m;
  double tk;

  // Some example content.
  h = 0.1;
  tk = 0.0;
  init_values_default(r, v, a, m);

  // Allow to input the data with a file.
  if (read_from_file) {
    init_values_from_file(r, v, m, input_filename);
  }

//   calc_accel_multiple(r, a, m);

  double P = calc_periode(m);

  integration_start(r, v, a, m);

  // Here comes the main loop
  int count = 0;
  int steps_per_orbit = 100;
  int t_max = calc_t_max(P, P_count, steps_per_orbit);

  h = P / 100;

  while (count < t_max) {
    calc_accel_multiple(r, a, m);
    integration_method(r, v, a, m, h);

    count++;

    if (write_to_files) {
      output_movement_data(r, v, a, m, output_file);

      // Calc all needed variab10les and output them into files.
      vector2d r_rel = r[1] - r[0];
      vector2d v_rel = v[1] - v[0];

      double great_half_axis = calc_great_half_axis(r_rel, v_rel, m);
      double excentric = calc_excentric(r_rel, v_rel, m, great_half_axis);
      double energy = calc_energy(r, v, m);
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

/**
 * Output the movement of the bodies itself to a file.
 */
void output_movement_data(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, std::vector< double >& m, ofstream &output_file = emptystream) {
  // headers
//   cout << "x \t y \t vx \t vy \t ax \t ay \t m" << endl;
  if (output_file.is_open()) {
    for (vector< vector<int> >::size_type i = 0; i < r.size(); i++) {
      // Just output the data of the second body, which is moving
      output_file << r[i] << "\t";
      output_file << v[i] << "\t";
      output_file << a[i] << "\t";
//       output_file << m[i];
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

void init_values_default(listv2d& r, listv2d& v, listv2d& a, listdouble& m) {
  double e = 0.3;
  double m2 = 1e-3;

  vector2d r1, r2;
  vector2d v1, v2;

  r1.y = 0.0;
  r2.y = 0.0;

  double dp = 1.0 - e;
  r1.x = - 1.0 * dp * m2 / (1.0 + m2);
  r2.x = dp * (1.0 + m2);

  v1.x = 0.0;
  v2.x = 0.0;

  // L = \mu * sqrt((1-e^2) * G * M * a)
  double mu = m2/(1.0 + m2);
  double L = mu * sqrt((1.0 - e*e) * (1.0 + m2));
  v2.y = (L / (dp * m2));
  v1.y = - L / dp;

  m.push_back(1.0);
  m.push_back(m2);

  r.push_back(r1);
  r.push_back(r2);
  v.push_back(v1);
  v.push_back(v2);

  vector2d a1;
  a1.x = 0.0;
  a1.y = 0.0;
  vector2d a2;
  a2.x = 0.0;
  a2.y = 0.0;
  a.push_back(a1);
  a.push_back(v2);
}

/**
 * Read the initial data from a textfile.
 */
void init_values_from_file(listv2d& r, listv2d& v, listdouble& m, string input_filename) {
  string line;

  char* input_filename_char = const_cast<char*>(input_filename.c_str());
  ifstream input(input_filename_char);

  vector<string> tokens;

  if (input.is_open()) {
    r.clear();
    v.clear();
    m.clear();

    while (input.good()) {
      tokens.clear();
      getline(input, line);
      split(line, " ", tokens);

      vector2d r1, v1;
      double m1 = 0.0;

      r1.x = convertToDouble(tokens[0]);
      r1.y = convertToDouble(tokens[1]);
      v1.x = convertToDouble(tokens[2]);
      v1.y = convertToDouble(tokens[3]);
      m1 = convertToDouble(tokens[4]);

      r.push_back(r1);
      v.push_back(v1);
      m.push_back(m1);
    }
    input.close();
  }
}
