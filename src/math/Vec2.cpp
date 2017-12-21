#include "Vec2.h"

Vec2::Vec2 () : x(0), y(0) {}

Vec2::Vec2 (float x, float y) : x(x), y(y) {}

Vec2::Vec2 (const Vec2 &v) : x(), y() {this->x = v.x; this->y = v.y;}

double Vec2::length() {
    return std::sqrt(x*x + y*y);
}
