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

double integrate_trapez_precision(
  double (*function) (double x),
  double start, double end,
  double precision);

double static_cache(int key, int value = 0);

double sinus(double x) {
  return sin(x);
}

double parabel(double x) {
  return x * x;
}

double gerade(double x) {
  return 1.0;
}

double func_si(double x) {
  // Lim x -> 0 = 1.
  if (x == 0) {
    return 1.0;
  }
  return sin(x) / x;
}

double func_c(double x) {
  return cos(M_PI * x * x / 2);
}
