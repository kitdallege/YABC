#ifndef VEC2_H
#define VEC2_H
#include <cmath>

struct Vec2 {
    float x;
    float y;

    Vec2 ();
    Vec2 (float x, float y);
    Vec2 (const Vec2 &v);
    double length();
};

#endif // VEC2_H
