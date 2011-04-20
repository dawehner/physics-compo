#include <iostream>
#include <math.h>
#include "iteration.cc"
using namespace std;

const int ITERATION_EASY = 0;
const int ITERATION_NEWTON = 1;

int ITERATION = ITERATION_EASY;
ofstream emptystream;

/**
 * This code could be OPP.
 */
double e_next(double anomalie_excent, double excent, double anomalie_middle) {
  switch (ITERATION) {
    case ITERATION_EASY:
    return iteration_easy(anomalie_excent, excent, anomalie_middle);
  default:
  case ITERATION_NEWTON:
    return iteration_newton(anomalie_excent, excent, anomalie_middle);
  }
}

double m_current(double anomalie_excent, double excent, double anomalie_middle) {
  return anomalie_excent - excent * sin(anomalie_excent);
}


float generate_anomalie_excent(double excent, double anomalie_middle, ofstream &output_file = emptystream) {
  double anomalie_excent = anomalie_middle;
  double anomalie_excent_last = 0;

  int i = 0;
  double min = 10e-9;
  while (((anomalie_excent - anomalie_excent_last) > min) && i < 10000) {
    anomalie_excent_last = anomalie_excent;
    anomalie_excent = e_next(anomalie_excent, excent, anomalie_middle);
    i++;
  }

  if (output_file.is_open()) {
    output_file << " " << i << endl;
  }

  return anomalie_excent;
}

float generate_anomalie_excent_per_time(double excent, double t, double t0, double P, ofstream &output_file = emptystream) {
 // Generate a middle anomalie to calc with.
  double anomalie_middle = 2 * 3.1415926 * (t - t0) / (P);
  return generate_anomalie_excent(excent, anomalie_middle, output_file);
}