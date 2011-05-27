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

double sinus(double x);
double parabel(double x);
double gerade(double x);
double func_si(double x);
double func_c(double x);