#ifndef SOLARSYSTEM_OBJECT_H
#define SOLARSYSTEM_OBJECT_H
#include "vector.cpp"

class solarsystem_object {

public:
    solarsystem_object(double _m, double _rad, vector2d _r, vector2d _v, vector2d _a);
    virtual ~solarsystem_object();
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

#endif // SOLARSYSTEM_OBJECT_H
