#include "solarsystem_object.h"
#include <vector>

solarsystem_object::solarsystem_object(double _m, double _rad, vector2d _r, vector2d _v, vector2d _a) {
  m = _m;
  rad = _rad;
  r = _r;
  v = _v;
  a = _a;
}

solarsystem_object::~solarsystem_object() {
  delete m;
  delete rad;
  delete r;
  delete v;
  delete a;
}

