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
  return 1.0;
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
  value = integrate_adaptive(&func_c, 0, x, 0.02);
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
  double delta = pow(10, -17);
  double epsilon = pow(10, -8);
  int_schatz =  int_schatz * epsilon / delta;


  vector<double> func_values;
  vector<double> func_pos_a;


  // Startwerte setzen:
  func_values[0] = function(start);
  func_values[1] = function(end);
  func_pos_a[0] = start;
  func_pos_a[1] = end;

  double int_sum = 0.0;
  int grenze_links_j = 0;
  int grenze_rechts_k = 1;
  int p = 1;
  int tiefe_l;

  vector<double> u;
  u[1] = 1;

  double h = 0.0;
  double m = 0.0;
  double fm = 0.0;
  double int_1 = 0.0;
  double int_2 = 0.0;

  do {
    cout << 123 << endl;
    h = func_pos_a[grenze_rechts_k] - func_pos_a[grenze_links_j];
    m = (func_pos_a[grenze_rechts_k] + func_pos_a[grenze_links_j]) / 2;

    fm = function(m);
    int_1 = h*(func_values[grenze_links_j] + func_values[grenze_rechts_k]) / 2;
    int_2 = (int_1 + 2 * h * fm) / 3;

    // Genauigkeit beachten
    if ((int_schatz + int_1 != int_schatz + int_2)) {
      p++;
      func_pos_a[p] = m;
      func_values[p] = fm;
      grenze_rechts_k = p;
      tiefe_l++;
      cout << 123 << endl;
      u[tiefe_l] = p;
    }
    else {
      int_sum += int_2;
      grenze_links_j = u[tiefe_l];
      tiefe_l --;
      grenze_rechts_k = u[tiefe_l];
    }
  }
  while (tiefe_l > 0);

  return int_sum;
}

