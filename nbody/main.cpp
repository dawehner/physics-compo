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
#include <boost/program_options.hpp>

/**
 * @TODO
 * Big major todo: throw away the vector2d code and just use an array!!!!
 */

using namespace std;
using namespace boost;
namespace po = boost::program_options;

ofstream emptystream;

int main(int argc, char **argv) {
  void (*integration_method) (listv2d& r, listv2d& v, listv2d& a, const listdouble& m, double h, double ti);

  int integration_method_value = INTEGRATION_RUNGE_KUTTA;
  string output_filename_prefix = "output";
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


  // Describe the availible programm options.
  po::options_description desc("Allowed options", 1024);
  desc.add_options()
    ("help", "Produce help message")
    ("timestamp-adaption,t", po::value<bool>(&adapt_timestamp)->default_value(false), "Adapt timestamp")
    ("integration-method,i", po::value<int>(&integration_method_value)->default_value(0), "Integration method")
    ("output,o", po::value<string>(&output_filename_prefix)->default_value("output"), "The output file prefix")
    ("write-to-files,w", po::value<bool>(&write_to_files)->default_value(true), "Write to files at all")
    // @todo: This should be named different.
    ("time-step,h", po::value<double>(&h)->default_value(0.0), "The default time-step size")
    ("period-counts,c", po::value<int>(&P_count)->default_value(10), "How many orbits should be calculated")
    ("steps-per-orbit,s", po::value<int>(&steps_per_orbit)->default_value(100), "The initial amount of steps per orbit")
    ("input,f", po::value<string>(&input_filename)->default_value(""), "Specify the file which has the initial parameters")
    ("break-closed-encounters,e", po::value<bool>(&break_closed_encounter)->default_value(false), "Should the programm be stoped if a closed encounter is detected")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << desc << endl;
    return EXIT_FAILURE;
  }

  switch (integration_method_value) {
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
//     case INTEGRATION_ANALYTIC:
//       integration_method = integration_analytic;
//       break;
    case INTEGRATION_LEAPFROG:
      integration_method = integration_leap_frog;
      break;
  }

  ofstream output_file;
  string output_filename = output_filename_prefix + ".dat";
  output_file.open(output_filename.c_str());

  ofstream output_file_conserved;
  output_filename = output_filename_prefix + "-conserved.dat";
  output_file_conserved.open(output_filename.c_str());

  ofstream output_file_encounters;
  output_filename = output_filename_prefix + "-encounters.dat";
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
  listdouble list_total_mass, list_start_energy, list_start_great_half_axis, list_start_excentric;
  for (int i = 1; i < ITEMS; i++) {
    vector2d r_rel = r[i] - r[0];
    vector2d v_rel = v[i] - v[0];

    list_total_mass.push_back(calc_total_mass(m, i));
    list_start_energy.push_back(calc_energy(r, v, m, i));
    vector3d j = calc_specific_angular_momentum(r_rel, v_rel);
    vector3d e = calc_runge_lenz(j, r_rel, v_rel, list_total_mass[i-1]);
    list_start_excentric.push_back(norm(e));
    list_start_great_half_axis.push_back(calc_great_half_axis(j, list_total_mass[i-1], list_start_excentric[i-1]));
  }

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

    if (false) {
      calc_accel_change_multiple(r, v, da, m);
      nbody_adapt_timestamp(time_per_step, dt, a, da);
    }

    count++;
    ti += dt;

    if (write_to_files) {
      output_movement_data(r, v, a, m, output_file);


      // @todo
      // Move this all to a new funciton.
      int size = r.size();
      for (int i = 1; i < size; i++) {
        // Calc all needed variab10les and output them into files.
        vector2d r_rel = r[i] - r[0];
        vector2d v_rel = v[i] - v[0];

        double energy = calc_energy(r, v, m, i) - list_start_energy[i-1];
        vector3d j = calc_specific_angular_momentum(r_rel, v_rel);
        vector3d e = calc_runge_lenz(j, r_rel, v_rel, list_total_mass[i-1]);
        double excentric = norm(e) - list_start_excentric[i-1];
        double great_half_axis = calc_great_half_axis(j, list_total_mass[i-1], excentric) - list_start_great_half_axis[i-1];

        vector2d R = calc_mass_center(r, m, list_total_mass[i-1], i);

        output_converseved_quantities(output_file_conserved,
                                      ti, abs(energy), norm(j) * m[i], abs(great_half_axis), excentric, norm(j), R);
      }
      bool closed_encounter = main_detect_closed_encounter(count_encounter, m, R_in, r, ti);
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
    output_file_encounters << count_encounter << endl;
    cout << "encounters: " << count_encounter << endl;
  }
  output_file_encounters.close();

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
void output_converseved_quantities(std::ofstream& output_file_conserved,
    double ti, double E1, double L1, double great_half_axis, double excentric, const double j, const vector2d& R) {
  if (output_file_conserved.is_open()) {
    output_file_conserved << scientific
    << ti << "\t"
    << E1 << "\t"
    << L1 << "\t"
    << great_half_axis << "\t"
    << excentric << "\t"
    << j << "\t" 
    << R.x << "\t"  << R.y << endl;
  }
}

void nbody_adapt_timestamp(const double& dt_begin, double& dt, listv2d& a, listv2d& da) {
  double min = numeric_limits<double>::max();
  double val = 0.0;
  int size = a.size();
  for (int i = 0; i < size; i++) {
    val = norm(a[i]) / norm(da[i]);
    min = min <= val ? min : val;
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
        double distance = metrik(r[j], r[i]);
        double R_in_heavier = m[i] < m[j] ? R_in[i] : R_in[j];
//         cout << R_in_heavier << endl;
        if (distance < R_in_heavier) {
//         cout << ti << " " << i << " " << j << " " << distance << " " << R_in_heavier << endl;
//           cout << r[i] << endl;
//           cout << r[j] << endl;
          count_encounter++;
          ret = true;
        }
      }
    }
  }

  return ret;
}