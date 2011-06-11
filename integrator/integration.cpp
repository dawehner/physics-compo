#ifndef INTEGRATION_CPP
#define INTEGRATION_CPP

#include "integration.h"

void integration_rk4(listDouble& y, listDouble& dydx, const double x, const double h, listDouble& y_out,
  void derivative(const double x, listDouble& y, listDouble& dyxy_out)) {

  // @todo: Benchmark whether this operation is slow, probably not.
  int size = y.size();

  listDouble K1(size), K2(size), K3(size), K4(size);

}
void integration_euler(listDouble& y, listDouble& dydx, const double x, const double h, listDouble& y_out,
  void derivative(const double x, listDouble& y, listDouble& dyxy_out)
);

#endif