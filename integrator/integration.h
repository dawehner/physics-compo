#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <cmath>
#include <vector>

using namespace std;

typedef vector <double> listDouble;

/**
 * Calculate the next values via the runge kutta method.
 *
 * @todo: Link some documentation about runge kutta.
 * The output is as always y_out.
 */
void integration_rk4(listDouble& y, listDouble& dydx, const double x, const double h, listDouble& y_out,
  void derivative(const double x, listDouble& y, listDouble& dyxy_out));

/**
 * Calculate the next values via the euler method.
 */
void integration_euler(listDouble& y, listDouble& dydx, const double x, const double h, listDouble& y_out,
  void derivative(const double x, listDouble& y, listDouble& dyxy_out));

#endif