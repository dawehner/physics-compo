#include "function.cc"
#include <cmath>

double iteration_easy(double anomalie_excent, double excent, double anomalie_middle) {
  return anomalie_middle + excent * sin(anomalie_excent);
}

double iteration_newton(double anomalie_excent, double excent, double anomalie_middle) {
  double funcvalue = function(anomalie_excent, excent, anomalie_middle);
  double diffvalue = function_diff(anomalie_excent, excent, anomalie_middle);
  double result = anomalie_excent
    - (funcvalue / diffvalue);
  return result;
}