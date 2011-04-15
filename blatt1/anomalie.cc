#include <iostream>
#include "iteration.cc"
using namespace std;

const int ITERATION_EASY = 0;
const int ITERATION_NEWTON = 1;

const int ITERATION = ITERATION_EASY;

/**
 * This code could be OPP.
 */
double e_next(double anomalie_excent, double excent, double anomalie_middle) {
  // std::cout << "e_next: E:" << anomalie_excent << ":M:" << anomalie_middle << ":e:" << excent << std::endl;
  switch (ITERATION) {
    case ITERATION_EASY:
	  return iteration_easy(anomalie_excent, excent, anomalie_middle);
	case ITERATION_NEWTON:
	  return iteration_newton(anomalie_excent, excent, anomalie_middle);
  }
}

double m_current(double anomalie_excent, double excent, double anomalie_middle) {
  return anomalie_excent - excent * sin(anomalie_excent);
}


float generate_anomalie_excent(double excent, double anomalie_middle) {
  double anomalie_excent = anomalie_middle;
  double anomalie_excent_last = 0;
  cout << "e:" << excent << "m:" << anomalie_middle << endl;
  
  int i = 0;
  double min = 0.000000001;
  while (((anomalie_excent - anomalie_excent_last) > min) && i < 10) {
	  // std::cout << "E:" << anomalie_excent << ":M:" << anomalie_middle << ":phi:" << phi << std::endl ;
    anomalie_excent_last = anomalie_excent;
	  anomalie_excent = e_next(anomalie_excent, excent, anomalie_middle);
	  i++;
  }
  cout << ":count:" << i;

  return anomalie_excent;
}
 
 float generate_anomalie_excent_per_time(double excent, double t, double t0, double P) {
 // Generate a middle anomalie to calc with.
  double anomalie_middle = 2 * 3.1415926 * (t - t0) / (P);
  // cout << "am:" << anomalie_middle << endl;
  return generate_anomalie_excent(excent, anomalie_middle);
}
