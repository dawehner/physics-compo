#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


double integrate_trapez(
  double (*function) (double x),
  double start, double end,
  double step_size);


double integrate_easy (
  double (*function) (double x),
  double start, double end,
  double step_size);

double integrate_adaptive (
  double (*function) (double x),
  double start, double end,
  double step_size);

double sinus(double x) {
  return sin(x);
}

double parabel(double x) {
  return x * x;
}

double gerade(double x) {
  return 1;
}

double si(double x) {
  return sin(x) / x;
}

double func_c(double x) {
  return cos(M_PI * x * x / 2);
}

int main() {
  double x = 3;
  double value = integrate_easy(&si, 0, x, 0.02);
  cout << value << endl;
  value = integrate_trapez(&func_c, 0, x, 0.02);
  cout << value << endl;
  return 0;
}


double integrate_easy(
  double (*function) (double x),
  double start, double end,
  double step_size) {

  double left_side = start;
  double sum;
  while (left_side < end) {
    left_side += step_size;
    sum += step_size * function(left_side);
  }

  return sum;
}

double integrate_trapez(
  double (*function) (double x),
  double start, double end,
  double step_size) {

  double left_side = start;
  double right_side = start;
  double value_left_side = 0.0;
  double value_right_side = function(left_side + step_size);

  double sum = 0.0;

  int count_function_call = 0;
  while (left_side < end) {
    // Use the last right_side. We use constant step size.
    left_side = right_side;
    right_side = left_side + step_size;
    value_left_side = value_right_side;
    value_right_side = function(right_side);
    count_function_call ++;
    sum += (right_side - left_side) / 2 * (value_left_side + value_right_side);
  }
  cout << count_function_call << endl;

  return sum;
}

double integrate_adaptive (
  double (*function) (double x),
  double start, double end,
  double step_size) {


  // Schaetzintegral berechnen.
  double int_schatz = integrate_trapez(function, start, end, step_size);
  // Maschinengenauigkeit beachten.
  double delta = e-20;
  double epsilon = e-8;
  int_schatz =  int_schatz * epsilon / delta;

  vector <double> ai;
  vector <double> fi;
  vector <double> ui;

  // Startwerte setzen
  ai[0] = start;
  ai[1] = end;
  fi[0] = function(start);
  fi[1] = function(end);
  double sum = 0.0;
  
  double j = 0;
  double k = 1;
  double p = 1;
  double l = 1;
  double ui[1] = 1;
  double fm = 0.0;

  double m = 0.0;

  while (l > 0) {
    h = ai[k] - ai[j];
    
    m = (ai[j] + ai[k]) / 2;
    fm = function(m);
  }    
}

