#include <cmath>

double function(double anomalie_excent, double excent, double anomalie_middle) {
  return anomalie_excent - excent * sin(anomalie_excent) - anomalie_middle;
}

double function_diff(double anomalie_excent, double excent, double anomalie_middle) {
  return 1.0 - excent * cos(anomalie_excent);
}
