#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "integration.cpp"
#include <fstream>
#include "quantities.cpp"
#include <vector>
#include <limits>
#include "main.h"

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

/**
 * @TODO
 * Big major todo: throw away the vector2d code and just use an array!!!!
 */

using namespace std;
using namespace boost;

ofstream emptystream;

int main(int argc, char **argv) {
  int c;
  void (*integration_method) (listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, double ti);

  int _integration_method = INTEGRATION_RUNGE_KUTTA;
  string filename = "output";
  bool write_to_files = true;

  string input_filename = "";

  double h = 0.0;
  double tk = 0.0;
  int P_count = 10;
  int steps_per_orbit = 100;
  int count_encounter = 0;

  // Should the timestamp be changed based on the values.
  bool adapt_timestamp = false;
  // Should the programm stop, once a closed encounter got detected
  bool break_closed_encounter = false;

  // Load data from input
  while ((c = getopt(argc, argv, "i:o:h:c:s:t::f:e::")) != -1) {
    switch (c) {
      // Set interation method
      case 'i':
        _integration_method = atof(optarg);
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
      case 't':
        adapt_timestamp = true;
      case 'f':
        if (input_filename == "") {
          input_filename = optarg;
        }
        break;
      case 'e':
        break_closed_encounter = true;
        break;
    }
  }

  switch (_integration_method) {
    case INTEGRATION_EULER:
      integration_method = integration_euler;
      break;
    case INTEGRATION_HEUN:
      integration_method = integration_heun;
      break;
    case INTEGRATION_RUNGE_KUTTA:
      integration_method = integration_rk4;
      break;
    case INTEGRATION_VERLET:
      integration_method = integration_verlet;
      break;
    case INTEGRATION_ANALYTIC:
      integration_method = integration_analytic;
      break;
    case INTEGRATION_LEAPFROG:
      integration_method = integration_leap_frog;
      break;
  }

  ofstream output_file;
  string output_filename = filename + ".dat";
  output_file.open(output_filename.c_str());

  ofstream output_file_conserved;
  output_filename = filename + "-conserved.dat";
  output_file_conserved.open(output_filename.c_str());

  ofstream output_file_encounters;
  output_filename = filename + "-encounters.dat";
  output_file_encounters.open(output_filename.c_str());


  if (!output_file.is_open()) {
    cout << "Couldn't open file to write." << endl;
    return EXIT_FAILURE;
  }


  listv2d r; // Place of the bodies
  listv2d v; // Speed of the bodies
  listv2d a; // Accel. of the bodies
  listv2d da; // Change of the accel. of the bodies
  listdouble m;

  // Load the startup config, or use some default configuration.
  if (input_filename.length() == 0) {
    cout << "Missing input filename" << endl;
    return EXIT_FAILURE;
  }
  else {
    main_body_load_from_file(r, v, a, da, m, h, tk, input_filename);
  }

  double P = calc_periode(m);

  main_prepare_mass_center_system(r, v, m);
  integration_start(r, v, a, m);

  // The hill-radius
  listdouble R_in(r.size());
  main_calc_influence_radius(R_in, m, r);

  // Calc initial values.
  vector2d r_rel = r[1] - r[0];
  vector2d v_rel = v[1] - v[0];
  double total_mass = calc_total_mass(m);
  double start_energy = calc_energy(r, v, m);
  double start_great_half_axis = calc_great_half_axis(r_rel, v_rel, m);
  double start_excentric = calc_excentric(r_rel, v_rel, m, start_great_half_axis);

  // Here comes the main loop
  int count = 0;
  const double time_per_step = P / steps_per_orbit;
  // dt is the actual used time per step, but maybe changed during runtime.
  double dt = time_per_step;
  int t_max = calc_t_max(P, P_count, steps_per_orbit);
  double ti = 0.0;

  h = P / 100.0;

  while (count < t_max) {
    calc_accel_multiple(r, a, m);
    integration_method(r, v, a, m, h, ti);

    if (adapt_timestamp) {
      calc_accel_change_multiple(r, v, da, m);
      nbody_adapt_timestamp(time_per_step, dt, a, da);
    }

    count++;
    ti += dt;

    if (write_to_files) {
      output_movement_data(r, v, a, m, output_file);

      // Calc all needed variab10les and output them into files.
      vector2d r_rel = r[1] - r[0];
      vector2d v_rel = v[1] - v[0];

      // @todo
      // Move this all to a new funciton.
      double great_half_axis = calc_great_half_axis(r_rel, v_rel, m) - start_great_half_axis;
      double excentric = calc_excentric(r_rel, v_rel, m, great_half_axis) - start_excentric;
      double energy = calc_energy(r, v, m) - start_energy;
//       double angular_momentum = calc_angular_momentum(m, great_half_axis, excentric);
      double angular_momentum = 0.0;
      vector3d j = calc_specific_angular_momentum(r[0], v[0]);
      vector2d R = calc_mass_center(r, m, total_mass);
      vector3d runge_lenz_e = calc_runge_lenz(j, v[0], r[0], total_mass);
      double j_amount = norm(j);
      double R_amount = norm(R);
      double runge_lenz_e_amount = norm(runge_lenz_e);

      output_converseved_quantities(output_file_conserved, ti, energy, angular_momentum, great_half_axis, excentric, j_amount, runge_lenz_e_amount, R);
      double closed_encounter = main_detect_closed_encounter(count_encounter, m, R_in, r, ti);
      if (closed_encounter && break_closed_encounter) {
        return EXIT_FAILURE;
      }
    }

  }

  if (output_file.is_open()) {
    output_file.close();
  }
  if (output_file_conserved.is_open()) {
    output_file_conserved.close();
  }

  if (!break_closed_encounter) {
    cout << "encounters: " << count_encounter << endl;
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
    int size = r.size();
    for (int i = 0; i < size; i++) {
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
 * Output the energy/angular momentum and many more.
 */
void output_converseved_quantities(std::ofstream& output_file_conserved, double ti, double E1, double L1, double great_half_axis, double excentric, const double j, const double e, const vector2d& R) {
  if (output_file_conserved.is_open()) {
    output_file_conserved << scientific
    << ti << "\t"
    << E1 << "\t"
    << L1 << "\t"
    << great_half_axis << "\t"
    << excentric << "\t"
    << j << "\t" 
    << e << "\t" 
    << R.x << "\t"  << R.y << endl;
  }
}

void nbody_adapt_timestamp(const double& dt_begin, double& dt, listv2d& a, listv2d& da) {
  double min = numeric_limits<double>::max();
  double val = 0.0;
  int size = a.size();
  for (int i = 0; i < size; i++) {
    val = norm(a[i]) / norm(da[i]);
    min = min >= val ? min : val;
  }
  dt = dt_begin * min;
}

void main_body_load_from_file(listv2d& r, listv2d& v, listv2d& a, listv2d& da, listdouble& m, double& h, double& tk, string& filename) {
  // @TODO
  //   - Allow to load this values.
  h = 0.1;
  tk = 0.0;

  ifstream file(filename.c_str());
  string input_str;

  vector2d a_dot_i;
  a_dot_i.x = 0.0;
  a_dot_i.y = 0.0;

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
    da.push_back(a_dot_i);
  }
}

void main_calc_influence_radius(listdouble& R_in, const listdouble& m, const listv2d& r) {
  int central_body = 0;

  int size = m.size();
  for (int i = 0; i < size; i++) {
    double mu = m[i] / m[central_body];
    R_in[i] = pow(mu, 2.0/5.0) * norm(r[i]);
//     cout << R_in[i] << endl;
  }
}

void main_prepare_mass_center_system(listv2d& r, listv2d& v, listdouble m) {
  listv2d r_ = r;
  listv2d v_ = v;

  // First find the center of mass.
  vector2d rcm;
  rcm.x = rcm.y = 0.0;
  double total_mass = 0.0;

  int size = r.size();
  for (int i = 0; i < size; i++) {
    rcm = rcm + m[i] * r[i];
    total_mass += m[i];
  }
  rcm = rcm / total_mass;

  // Replace the previous positions with the relative positions.
  for (int i = 0; i < size; i++) {
    r[i] = r[i] - rcm;
  }

  // Now do the same for the speeds.
  vector2d vcm;
  vcm.x = vcm.y = 0.0;

  for (int i = 0; i < size; i++) {
    vcm = vcm + m[i] * v[i];
  }
  vcm = vcm / total_mass;

  for (int i = 0; i < size; i++) {
    v[i] = v[i] - vcm;
  }
}


bool main_detect_closed_encounter(int& count_encounter, listdouble& m, listdouble& R_in, listv2d& r, const double ti) {
  bool ret = false;
  int size = R_in.size();

  // Check the encounter foreach particle to each particle.
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i != j) {
        double distance = metrik(r[i], r[j]);
        double R_in_heavier = m[i] < m[j] ? R_in[i] : R_in[j];
        if (distance < R_in_heavier) {
          cout << ti << " " << i << " " << j << " " << distance << " " << R_in_heavier << endl;
          cout << r[i] << endl;
          cout << r[j] << endl;
          count_encounter++;
          ret = true;
        }
      }
    }
  }

  return ret;
}