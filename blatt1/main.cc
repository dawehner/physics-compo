#include <cmath>

const int ITERATION_EASY = 0;
const int ITERATION_NEWTON = 1;

const int ITERATION = ITERATION_EASY;


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
  return anomalie_excent
    - function(anomalie_excent, excent, anomalie_middle)
    / function_diff(anomalie_excent, excent, anomalie_middle);
}

/**
 * This code could be OPP.
 */
float e_next(float anomalie_excent, float excent, float anomalie_middle) {
  switch (ITERATION) {
    case ITERATION_EASY:
	  return iteration_easy(anomalie_excent, excent, anomalie_middle);
	case ITERATION_NEWTON:
	  return iteration_newton(anomalie_excent, excent, anomalie_middle);
  }
}

  


/**
 * Generate some variables.
 */
 // function calc_phi(float anomalie_excent, float excent) {
   // return 2 * atan(
     // sqrt((1+excent)/(1-
	 
	 
int main() {
  float anomalie_excent, excent, anomalie_middle;
  while (true) {
	anomalie_excent = e_next(anomalie_excent, excent, anomalie_middle);
  }

  return 0;
}