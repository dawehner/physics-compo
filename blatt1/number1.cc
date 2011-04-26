#include <cmath>
#include <iostream>
#include <fstream>
#include "anomalie.cc"
#include "coordinates.cc"
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  double excent = 0.205;
  double phi = 0;
  double r = 0;
  double x = 0;
  double y = 0;
  double a = 1;
  double phi0 = 0;
  char *output_filename = "output1.dat";
  int c;

  // Load data from input
  while ((c = getopt(argc, argv, ":i:e:o:")) != -1) {
    switch (c) {
      // Set interation method
      case 'i':
        ITERATION = atof(optarg);
        break;
      // set excent value
      case 'e':
        excent = atof(optarg);
        break;
      // set outputfilename
      case 'o':
        output_filename = optarg;
        break;
    }
  }


  ofstream output_file;
  output_file.open(output_filename);

  if (!output_file.is_open()) {
    cout << "Couldn't open file to write." << endl;
    return EXIT_FAILURE;
  }

  // Generate 100 values of M and calculate the E for it.
  // Additional the count of steps are counted and printed out.
  double anomalie_middle = 0.0;
  double anomalie_excent = 0.0;

  for (int i = 0; i < 100; i++) {
    // Write previous row first.
    phi = calc_phi(anomalie_excent, excent);
    cout << phi << " ";
    r = calc_r(a, excent, phi, phi0);
    cout << r << endl;
    x = calc_x(r, phi, phi0);
    y = calc_y(r, phi, phi0);

    output_file << anomalie_middle << " " << x << " " << y;
    // Generate a value between 0 and 2pi
    anomalie_middle = ((2 * M_PI) / 100) * i;
    anomalie_excent  = generate_anomalie_excent(excent, anomalie_middle, output_file);
//     cout << anomalie_excent << endl;
//     output_file << endl;
  }

  output_file.close();

  return 0;
}
