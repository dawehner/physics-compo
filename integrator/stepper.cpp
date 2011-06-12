#ifndef STEPPER_CPP
#define STEPPER_CPP

#include "stepper.h"

void stepper_simple(listDouble& y, const double x, const double h,
  void derivative(const double x, listDouble& y, listDouble& dyxy_out),
  void integrator(listDouble& y, listDouble& dydx, const double x, const double h, listDouble& y_out,
    void derivative(const double x, listDouble& y, listDouble& dyxy_out))) {

  listDouble& dyxy(y.size());
  listDouble& y_out(y.size());

  derivative(y, x, dyxy);
  integrator(y, dyxy, x, h, y_out, derivative);
}

#endif