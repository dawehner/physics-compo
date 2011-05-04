#include <cmath>
using namespace std;

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
  inline double metrik(_Tp __a, _Tp __b) {
    return norm(__a - __b);
  }

// @todo:
//   A fast metrik for vector2d/vector3d could be written here.

inline double norm(vector2d vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y);
}

inline double norm(vector3d vec) {
  return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}
