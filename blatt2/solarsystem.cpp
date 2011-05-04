#include "vector.cpp"

/**
 * @todo
 *    Figure out a way to store both vector2d/vector3d of r, v, a.
 */
struct solarsystem_object {
  // Total mass of the object.
  double m;
  // Radius of the object.
  double rad;
  // The current position of the object.
  vector2d r;
  // The current vecolicity of the object.
  vector2d v;
  // The current acceleration of the object.
  vector2d a;
};
