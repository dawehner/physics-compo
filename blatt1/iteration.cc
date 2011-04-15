#include "function.cc"

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