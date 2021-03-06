#include <cmath>
#include <vector>
#include "vector.h"

#ifndef VECTOR_CPP
#define VECTOR_CPP

using namespace std;

typedef vector< vector2d> listv2d;
typedef vector< double> listdouble;

struct vector2d {
  double x;
  double y;
};

struct vector3d {
  double x;
  double y;
  double z;
};

vector2d operator-(vector2d vec1, vector2d vec2) {
  vector2d vec;
  vec.x = vec1.x - vec2.x;
  vec.y = vec1.y - vec2.y;
  return vec;
}

vector2d operator+(vector2d vec1, vector2d vec2) {
  vector2d vec;
  vec.x = vec1.x + vec2.x;
  vec.y = vec1.y + vec2.y;
  return vec;
}

void operator+=(vector2d& vec1, vector2d vec2) {
  vec1.x += vec2.x;
  vec1.y += vec2.y;
}

void operator*=(vector2d& vec1, double number) {
  vec1.x *= number;
  vec1.y *= number;
}


vector2d operator*(vector2d vec1, double number) {
  vector2d vec;
  vec.x = vec1.x * number;
  vec.y = vec1.y * number;
  return vec;
}

vector2d operator*(double number, vector2d vec1) {
  vector2d vec;
  vec.x = vec1.x * number;
  vec.y = vec1.y * number;
  return vec;
}


vector2d operator/(vector2d vec1, double number) {
  vector2d vec;
  vec.x = vec1.x / number;
  vec.y = vec1.y / number;
  return vec;
}


vector3d operator-(vector3d vec1, vector3d vec2) {
  vector3d vec;
  vec.x = vec1.x - vec2.x;
  vec.y = vec1.y - vec2.y;
  vec.z = vec1.z - vec2.z;
  return vec;
}

double norm(vector2d vec);
double norm(vector3d vec);

template<typename _Tp>
  double metrik(_Tp __a, _Tp __b) {
    return norm(__a - __b);
  }

// @todo:
//   A fast metrik for vector2d/vector3d could be written here.

inline double norm(vector2d vec) {
  return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

double norm(vector3d vec) {
  return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

double metrik(vector2d vec1, vector2d vec2) {
  return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2));
}

ostream& operator<<(ostream& out, const vector2d& vec) {
    out << vec.x << "\t" << vec.y;
    return out;
}

#endif