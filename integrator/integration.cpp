#ifndef INTEGRATION_CPP
#define INTEGRATION_CPP

#include "integration.h"

void integration_rk4(listDouble& y, listDouble& dydx, const double x, const double h, listDouble& y_out,
  void derivative(const double x, listDouble& y, listDouble& dyxy_out)) {

  // @todo: Benchmark whether this operation is slow, probably not.
  int size = y.size();

  listDouble K1, K2, K3, K4;
  listDouble y_temp(size);

  K1 = dydx;

  const double h_2 = h/2;
  for (int i = 0; i < size; i++) {
    y_temp[i] = y[i] + h_2 * K1[i];
  }
  derivative(x, y_temp, K2);

  for (int i = 0; i < size; i++) {
    y_temp[i] = y[i] + h_2 * K2[i];
  }
  derivative(x, y_temp, K3);

  for (int i = 0; i < size; i++) {
    y_temp[i] = y[i] + h * K3[i];
  }
  derivative(x, y_temp, K4);

  // @todo: Find out whether the compiler automatically optimize it.
  const double h_6 = h/6;
  for (int i = 0; i < size; i++) {
    y_out[i] = y[i] + h_6 * (K1[i] + 2 * K2[i] + 2 * K3[i] + K4[i]);
  }
}
void integration_euler(listDouble& y, listDouble& dydx, const double x, const double h, listDouble& y_out,
  void derivative(const double x, listDouble& y, listDouble& dyxy_out)) {

  int size = y.size();
  for (int i = 0; i < size; i++) {
    y_out[i] = y[i] + dydx[i];
  }
}

#endif