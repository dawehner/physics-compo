#ifndef STEPPER_H
#define STEPPER_H

typedef vector <double> listDouble;

void stepper_simple(listDouble& y, const double x, const double h,
  void derivative(const double x, listDouble& y, listDouble& dyxy_out),
  void integrator(listDouble& y, listDouble& dydx, const double x, const double h, listDouble& y_out,
    void derivative(const double x, listDouble& y, listDouble& dyxy_out)));

#endif