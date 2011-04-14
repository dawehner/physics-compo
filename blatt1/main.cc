#include <cmath>
#include <iostream>

const int ITERATION_EASY = 0;
const int ITERATION_NEWTON = 1;

const int ITERATION = ITERATION_NEWTON;


float function(float anomalie_excent, float excent, float anomalie_middle) {
  return anomalie_excent - excent * sin(anomalie_excent) - anomalie_middle;
}

float function_diff(float anomalie_excent, float excent, float anomalie_middle) {
  return 1.0 - excent * cos(anomalie_excent);
}

float iteration_easy(float anomalie_excent, float excent, float anomalie_middle) {
  return anomalie_middle + excent * sin(anomalie_excent);
}

float iteration_newton(float anomalie_excent, float excent, float anomalie_middle) {
  float funcvalue = function(anomalie_excent, excent, anomalie_middle);
  float diffvalue = function_diff(anomalie_excent, excent, anomalie_middle);
  std::cout << "func:" << funcvalue << std::endl;
  return anomalie_excent
    - (funcvalue / diffvalue);
}

/**
 * This code could be OPP.
 */
float e_next(float anomalie_excent, float excent, float anomalie_middle) {
  std::cout << "e_next:" << anomalie_excent << excent << anomalie_middle << std::endl;
  switch (ITERATION) {
    case ITERATION_EASY:
	  return iteration_easy(anomalie_excent, excent, anomalie_middle);
	case ITERATION_NEWTON:
	  return iteration_newton(anomalie_excent, excent, anomalie_middle);
  }
}

float m_current(float anomalie_excent, float excent, float anomalie_middle) {
  std::cout << "m_current:" << anomalie_excent << excent << anomalie_middle << std::endl;
  return anomalie_excent - excent * sin(anomalie_excent);
}

  


/**
 * Generate some variables.
 */
 // function calc_phi(float anomalie_excent, float excent) {
   // return 2 * atan(
     // sqrt((1+excent)/(1-
	 
	 
int main() {
  float anomalie_excent = 0.2;
  float excent = 0.205;
  float anomalie_middle = 0.1;
  int i = 0;
  while (i < 5) {
	anomalie_middle = m_current(anomalie_excent, excent, anomalie_middle);
	anomalie_excent = e_next(anomalie_excent, excent, anomalie_middle);
	std::cout << "E:" << anomalie_excent << ":M:" << anomalie_middle << std::endl;
	i++;
  }

  return 0;
}