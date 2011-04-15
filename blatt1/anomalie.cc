
const int ITERATION_EASY = 0;
const int ITERATION_NEWTON = 1;

const int ITERATION = ITERATION_EASY;

#include "iteration.cc"
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

 
 

float generate_anomalie_excent(double excent, double t, double t0, double P) {
  double anomalie_excent_last = 0;
  double anomalie_middle = 2 * 3.1415926 * (t - t0) / (P);
  double anomalie_excent = anomalie_middle;
  
  int i = 0;
  while (((anomalie_excent - anomalie_excent_last) < 10^-9) && i < 100) {
	// std::cout << "E:" << anomalie_excent << ":M:" << anomalie_middle << ":phi:" << phi << std::endl ;
	anomalie_excent = e_next(anomalie_excent, excent, anomalie_middle);
	i++;
  }
}