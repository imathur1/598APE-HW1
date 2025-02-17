#include <limits>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <printf.h>
#include "vector.h"
#include <stddef.h>

Vector::Vector(double a, double b, double c) : x(a), y(b), z(c) {}
void Vector::operator-=(const Vector &rhs) {
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
}
void Vector::operator+=(const Vector &rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
}
void Vector::operator*=(const double rhs) {
  x *= rhs;
  y *= rhs;
  z *= rhs;
}
void Vector::operator*=(const float rhs) {
  x *= rhs;
  y *= rhs;
  z *= rhs;
}
void Vector::operator*=(const int rhs) {
  x *= rhs;
  y *= rhs;
  z *= rhs;
}
void Vector::operator/=(const double rhs) {
  x /= rhs;
  y /= rhs;
  z /= rhs;
}
void Vector::operator/=(const float rhs) {
  x /= rhs;
  y /= rhs;
  z /= rhs;
}
void Vector::operator/=(const int rhs) {
  x /= rhs;
  y /= rhs;
  z /= rhs;
}

/*
Vector Vector::operator * (const Vector a) {
   return Vector(y*a.z-z*a.y, z*a.x-x*a.z, x*a.y-y*a.x);
}*/

Ray::Ray(const Vector &po, const Vector &ve) : point(po), vector(ve) {}
