#include <iostream>
#include "vector.cpp"

using namespace std;

int main(int argc, char **argv) {
  vector2d test;
  test.x = 2;
  test.y = 2;

  vector2d test1;
  test1.x = 2;
  test1.y = 2;

  cout << norm(test) << endl;
  cout << norm(test1) << endl;
  cout << metrik(test, test1) << endl;
}
