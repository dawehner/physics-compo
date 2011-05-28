#include "static_helper.h"
#include "integration.h"

/**
 * This function just takes the function values in the middle between two intervalls * step_size.
 */
double integrate_easy(
  double (*function) (double x),
  double start, double end,
  double step_size) {

  double left_side = start;
  double sum;
  while (left_side < end) {
    left_side += step_size;
    sum += step_size * function(left_side + step_size/2);
  }

  return sum;
}

/**
 * Integrates a function with the trapez method.
 */
double integrate_trapez(
  double (*function) (double x),
  double start, double end,
  double step_size) {

  double left_side = start;
  double right_side = start;
  double value_left_side = 0.0;
  double value_right_side = function(left_side + step_size);

  double sum = 0.0;

  int function_calls = 0;
  while (left_side < end) {
    // Use the last right_side. We use constant step size.
    left_side = right_side;
    right_side = left_side + step_size;
    value_left_side = value_right_side;
    value_right_side = function(right_side);
    function_calls ++;
    sum += (right_side - left_side) / 2 * (value_left_side + value_right_side);
  }
  static_cache(STATIC_TRAPEZ, function_calls);
//   cout << count_function_call << endl;

  return sum;
}

/**
 * Use the trapez integration method to get a certain precision.
 */
double integrate_trapez_precision (
  double (*function) (double x),
  double start, double end,
  double precision) {

  // Set a default step size which isn't too small.
  double step_size = 0.02;
  double int_schatz = integrate_trapez(function, start, end, 0.02);

  double delta = pow(10, -17);
  double epsilon = precision;
  int_schatz *= epsilon / delta;

  double int_1 = 0.0;
  double int_2 = 0.0;

  int function_calls = 0;

  do {
    int_1 = int_2;
    step_size *= 0.5;

    // Hier kommt die eigentliche Integration mithilfe der Trapezregel bei einer bestimmen step_size.
    int_2 = integrate_trapez(function, start, end, step_size);
    function_calls += static_cache(STATIC_TRAPEZ);
  }
  while ((int_schatz + int_1) != (int_schatz + int_2));

  static_cache(STATIC_TRAPEZ_PRECISION, function_calls);

  return int_2;
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

  map<int, double> func_values;
  map<int, double> func_pos_a;


  // Startwerte setzen:
  func_values[0] = function(start);
  func_values[1] = function(end);
  func_pos_a[0] = start;
  func_pos_a[1] = end;

  double int_sum = 0.0;
  int grenze_links_j = 0;
  int grenze_rechts_k = 1;
  int p = 1;
  int tiefe_l = 1;

  map<int, double> u;
  u[1] = 1;

  double h = 0.0;
  double m = 0.0;
  double fm = 0.0;
  double int_1 = 0.0;
  double int_2 = 0.0;

  int function_calls = 2;

  do {
    h = func_pos_a[grenze_rechts_k] - func_pos_a[grenze_links_j];
    m = (func_pos_a[grenze_rechts_k] + func_pos_a[grenze_links_j]) / 2;

    // @todo
    // Find out whether this todo is valid.
    // @todo
    // This function is called too many times. There is no reason here to call the function itself all the time.
    // It might be called already and stored in func_values.
    fm = function(m);
    function_calls++;
    int_1 = h * (func_values[grenze_links_j] + func_values[grenze_rechts_k]) / 2;
    int_2 = (int_1 + 2 * h * fm) / 3;

    // Genauigkeit beachten
    if ((int_schatz + int_1 != int_schatz + int_2)) {
      // Genauigkeit ist noch nicht hoch genug
      // Also geht man eine ebene tiefer und verschiebt den rechten rand auf
      // den vorherigen mittelpunkt usw. bis man genau genug ist.
      p++;
      func_pos_a[p] = m;
      func_values[p] = fm;
      grenze_rechts_k = p;
      tiefe_l++;
      u[tiefe_l] = p;
    }
    else {
      // Nun ist die genauigkeit hoch genug.
      int_sum += int_2;
      // Wir gehen zum nächsten Internall und gehen erst einmal eine Ebene nach oben.
      grenze_links_j = u[tiefe_l];
      tiefe_l --;
      grenze_rechts_k = u[tiefe_l];
    }
  }
  while (tiefe_l > 0);
  static_cache(STATIC_ADAPTIVE, function_calls);

  return int_sum;
}