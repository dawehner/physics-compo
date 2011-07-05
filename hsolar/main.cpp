#include "hsolar.cpp"

int main(int argc, char **argv) {

  int c = 0;
  while ((c = getopt(argc, argv, ":o:")) != -1) {
    switch (c) {
      case 'o':
        HSOLAR_OSZILLATION = 1;
        break;
    }
  }
  hsolar_solve(100.0, 0.001, 1.5);
  return 0;
}