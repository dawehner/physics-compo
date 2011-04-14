#include <cmath>
#include <iostream>

const int ITERATION_EASY = 0;
const int ITERATION_NEWTON = 1;

const int ITERATION = ITERATION_NEWTON;


double function(double anomalie_excent, double excent, double anomalie_middle) {
  return anomalie_excent - excent * sin(anomalie_excent) - anomalie_middle;
}

double function_diff(double anomalie_excent, double excent, double anomalie_middle) {
  return 1.0 - excent * cos(anomalie_excent);
}

double iteration_easy(double anomalie_excent, double excent, double anomalie_middle) {
  return anomalie_middle + excent * sin(anomalie_excent);
}

double iteration_newton(double anomalie_excent, double excent, double anomalie_middle) {
  double funcvalue = function(anomalie_excent, excent, anomalie_middle);
  double diffvalue = function_diff(anomalie_excent, excent, anomalie_middle);
  double result = anomalie_excent
    - (funcvalue / diffvalue);
	
  // std::cout << "iteration_newton:intput: E:" << anomalie_excent << ":M:" << anomalie_middle << ":e:" << excent << std::endl;
  // std::cout << "iteration_newton: f:" << funcvalue << ":f':" << diffvalue << ":E:" << anomalie_excent << std::endl;
  return result;
}

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

  


/**
 * Generate some variables.
 */
 double calc_phi(double anomalie_excent, double excent) {
  return 2 * atan(
     sqrt((1+excent)/(1-excent)) *
	 tan(anomalie_excent / 2));
 }
	 
	 
int main() {
  double anomalie_excent = 1.7;
  double anomalie_excent_last = 0;
  double excent = 0.9;
  double anomalie_middle = 0.8;
  double phi = 0;
  int i = 0;
  while (((anomalie_excent - anomalie_excent_last) < 10^-9) && i < 100) {
	// std::cout << "E:" << anomalie_excent << ":M:" << anomalie_middle << ":phi:" << phi << std::endl ;
	std::cout << "phi:" << phi << std::endl;
	anomalie_excent = e_next(anomalie_excent, excent, anomalie_middle);
	//anomalie_middle = m_current(anomalie_excent, excent, anomalie_middle);
	phi = calc_phi(anomalie_excent, excent);

	i++;
  }

  return 0;
}