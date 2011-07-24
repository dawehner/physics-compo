#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "integration.cpp"
#include <fstream>
#include "quantities.cpp"
#include <vector>

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

ofstream emptystream;

void output_movement_data(vector< vector2d >& r, vector< vector2d >& v, vector< vector2d >& a, vector< double >& m, ofstream& output_file);
void output_converseved_quantities(double E1, double L1, ofstream& output_file_energy, ofstream& output_file_angular_momentum);
void output_orbital_parameters(double a1, double e1, ofstream& output_file_a, ofstream& output_file_e);
void main_two_body_start( listv2d& r, listv2d& v, listv2d& a, listdouble& m, double& h, double& tk);
void main_body_load_from_file( listv2d& r, listv2d& v, listv2d& a, listdouble& m, double& h, double& tk, string& filename);

int main(int argc, char **argv) {
  int c;
  void (*integration_method) (listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, double ti);

  int iteration = INTEGRATION_RUNGE_KUTTA;
  string filename = "output";
  bool write_to_files = true;

  string input_filename = "";

  double h = 0.0;
  double tk = 0.0;
  int P_count = 10;
  int steps_per_orbit = 100;

  // Load data from input
  while ((c = getopt(argc, argv, ":i:o:h:c:s:v:")) != -1) {
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
        P_count = (int) atof(optarg);
        break;
      case 's':
        steps_per_orbit = atof(optarg);
        break;
      case 'v':
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
    case INTEGRATION_LEAPFROG:
      integration_method = integration_leap_frog;
      break;
    case INTEGRATION_ANALYTIC:
      integration_method = integration_analytic;
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


  listv2d r;
  listv2d v;
  listv2d a;
  listdouble m;

  // Load the startup config, or use some default configuration.
  if (input_filename.length() == 0) {
    main_two_body_start(r, v, a, m, h, tk);
  }
  else {
    main_body_load_from_file(r, v, a, m, h, tk, input_filename);
  }

  double P = calc_periode(m);

  integration_start(r, v, a, m);

  // Here comes the main loop
  int count = 0;
  double time_per_step = P / (double) steps_per_orbit;
  int t_max = calc_t_max(P, P_count, steps_per_orbit);
  double ti = 0;

  h = P / 100;

  while (count < t_max) {
    calc_accel_multiple(r, a, m);
    integration_method(r, v, a, m, h, ti);

    count++;
    ti += time_per_step;

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
      output_file << scientific << r[i] << "\t";
      output_file << scientific << v[i] << "\t";
      output_file << scientific << a[i] << "\t";
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
    output_file_energy << scientific << E1 << endl;
  }
  if (output_file_angular_momentum.is_open()) {
    output_file_angular_momentum << scientific << L1 << endl;
  }
}


/**
 * Output the excentric/great half axis to a file.
 */
void output_orbital_parameters(double a1, double e1, ofstream& output_file_a, ofstream& output_file_e) {
  if (output_file_a.is_open()) {
    output_file_a << scientific << a1 << endl;
  }

  if (output_file_e.is_open()) {
    output_file_e << scientific << e1 << endl;
  }
}

void main_two_body_start(listv2d& r, listv2d& v, listv2d& a, listdouble& m, double& h, double& tk) {
  // Some example content.
  h = 0.1;
  tk = 0.0;

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
  a.push_back(a1);
  vector2d a2 = a1;
  a.push_back(v2);
}

void main_body_load_from_file(listv2d& r, listv2d& v, listv2d& a, listdouble& m, double& h, double& tk, string& filename) {
  // @TODO
  //   - Allow to load this values.
  h = 0.1;
  tk = 0.0;

  ifstream file(filename.c_str());
  string input_str;

  while (getline(file, input_str)) {
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    char_separator<char> sep(" ", "", boost::keep_empty_tokens);
    tokenizer tokens(input_str, sep);

    vector2d ri, vi, ai;
    double mi = 0.0;

    int count = 0;
    for (tokenizer::iterator beg = tokens.begin(); beg != tokens.end(); ++beg) {
      double value = lexical_cast<double>(*beg);
      switch (count++) {
        case 0:
          ri.x = value;
          break;
        case 1:
          ri.y = value;
          break;
        case 2:
          vi.x = value;
          break;
        case 3:
          vi.y = value;
          break;
        case 4:
          mi = value;
          break;
      }
    }
    ai.y = ai.x = 0.0;

    r.push_back(ri);
    v.push_back(vi);
    a.push_back(ai);
    m.push_back(mi);
  }
}