#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "iteration.cpp"


using namespace std;

// const double G = 6.6726e-11;
const double G = 1;

int test1(int a) {
  return a + 1;
}
int test2(int a) {
  return a - 1;
}

int main(int argc, char **argv) {
  int (*iterationMethod) (int);
  iterationMethod = test1;
  cout << iterationMethod(1) << endl;
  iterationMethod = test2;
  cout << iterationMethod(1) << endl;

  int c;
  // Load data from input
  while ((c = getopt(argc, argv, ":i")) != -1) {
    switch (c) {
      // Set interation method
      case 'i':
        int iteration = atof(optarg);
        switch (iteration) {
          case ITERATION_EULER:
          case ITERATION_HEUN:
          case ITERATION_RUNGE_KUTTA:
        }
        break;
      // set excent value
    }
  }
  return 0;
}
