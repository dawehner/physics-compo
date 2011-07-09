#include "hsolar.cpp"


int main(int argc, char **argv) {
  double time_end = 100.0;
  double time_step = 0.001;
  double poly_n = 1.5;

  int c;
  while ((c = getopt(argc, argv, ":n:e:t:o:")) != -1) {
    switch (c) {
      case 'e':
        time_end = atof(optarg);
        break;
      case 't':
        time_step = atof(optarg);
        break;
      case 'n':
        poly_n = atof(optarg);
        break;
      case 'o':
        HSOLAR_START = HSOLAR_START_OSCILLATION;
        break;
    }
  }

  hsolar_solve(time_end, time_step, poly_n);
  return 0;
}