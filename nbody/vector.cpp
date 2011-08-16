#include <cmath>
#include <vector>
#include "vector.h"

#ifndef VECTOR_CPP
#define VECTOR_CPP

using namespace std;

typedef vector< vector3d> listv3d;
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

vector3d operator-(vector3d vec1, vector3d vec2) {
  vector3d vec;
  vec.x = vec1.x - vec2.x;
  vec.y = vec1.y - vec2.y;
  vec.z = vec1.z - vec2.z;

  return vec;
}

vector3d operator+(vector3d vec1, vector3d vec2) {
  vector3d vec;
  vec.x = vec1.x + vec2.x;
  vec.y = vec1.y + vec2.y;
  vec.z = vec1.z + vec2.z;
  return vec;
}

void operator+=(vector3d& vec1, vector3d vec2) {
  vec1.x += vec2.x;
  vec1.y += vec2.y;
  vec1.z += vec2.z;
}

void operator*=(vector3d& vec1, double number) {
  vec1.x *= number;
  vec1.y *= number;
  vec1.z *= number;
}


vector3d operator*(vector3d vec1, double number) {
  vector3d vec;
  vec.x = vec1.x * number;
  vec.y = vec1.y * number;
  vec.z = vec1.z * number;

  return vec;
}

vector3d operator*(double number, vector3d vec1) {
  vector3d vec;
  vec.x = vec1.x * number;
  vec.y = vec1.y * number;
  vec.z = vec1.z * number;
  return vec;
}

double operator*(vector3d vec1, vector3d vec2) {
  double res;
  res = vec1.x * vec2.x + vec1.y * vec1.y + vec1.z * vec1.z;
  return res;
}

vector3d operator/(vector3d vec1, double number) {
  vector3d vec;
  vec.x = vec1.x / number;
  vec.y = vec1.y / number;
  vec.z = vec1.z / number;

  return vec;
}


double norm(vector3d vec);

template<typename _Tp>
  double metrik(_Tp __a, _Tp __b) {
    return norm(__a - __b);
  }

// @todo:
//   A fast metrik for vector2d/vector3d could be written here.

double norm(vector3d vec) {
  return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

double metrik(vector3d vec1, vector3d vec2) {
  return sqrt(pow(vec1.x - vec2.x, 2.0) + pow(vec1.y - vec2.y, 2.0) + pow(vec1.z - vec2.z, 2.0));
}

ostream& operator<<(ostream& out, const vector3d& vec) {
  out << scientific << vec.x << "\t" << vec.y;
  return out;
}

vector3d cross(vector3d vec1, vector3d vec2) {
  vector3d vec;
  vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
  vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
  vec.z = vec1.x * vec2.y - vec1.y * vec2.x;

  return vec;
}

vector3d vector2d_3d(vector2d vec1) {
  vector3d vec;
  vec.x = vec1.x;
  vec.y = vec1.y;
  vec.z = 0.0;

  return vec;
}

#endif