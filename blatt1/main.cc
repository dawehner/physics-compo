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
double calc_r(double a, double e, double phi, double phi0) {
  return a * (1 - e * e) / (1 + e * cos(phi - phi0));
}

double calc_x(double r, double phi, double phi0) {
  return r * cos(phi + phi0);
}

double calc_y(double r, double phi, double phi0) {
  return r * sin(phi + phi0);
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
	 
	 
int main() {
  double t = 0;
  double t0 = 0;
  double temp_except = 0;
  double excent = 0.205;
  double P = 1000;
  double phi = 0;
  
  for (int i = 0; i < 10000; i++) {
    t += i;
	
	temp_except = generate_anomalie_excent(excent, t, t0, P);
	phi = calc_phi(temp_except, excent);
	std::cout << "phi:" << phi << std::endl;
  }
  return 0;
}