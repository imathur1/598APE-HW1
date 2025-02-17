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

Vector Vector::operator-(const Vector &rhs) const {
  return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
}
Vector Vector::operator+(const Vector &rhs) const {
  return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}
/*
Vector Vector::operator * (const Vector a) {
   return Vector(y*a.z-z*a.y, z*a.x-x*a.z, x*a.y-y*a.x);
}*/
Vector Vector::operator*(const double rhs) const {
  return Vector(x * rhs, y * rhs, z * rhs);
}
Vector Vector::operator*(const float rhs) const {
  return Vector(x * rhs, y * rhs, z * rhs);
}
Vector Vector::operator*(const int rhs) const {
  return Vector(x * rhs, y * rhs, z * rhs);
}
Vector Vector::operator/(const double rhs) const {
  return Vector(x / rhs, y / rhs, z / rhs);
}
Vector Vector::operator/(const float rhs) const {
  return Vector(x / rhs, y / rhs, z / rhs);
}
Vector Vector::operator/(const int rhs) const {
  return Vector(x / rhs, y / rhs, z / rhs);
}
Vector Vector::cross(const Vector &a) const {
  return Vector(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
}
double Vector::mag2() const { return x * x + y * y + z * z; }
double Vector::mag() const { return sqrt(x * x + y * y + z * z); }
double Vector::dot(const Vector &a) const {
  return x * a.x + y * a.y + z * a.z;
}
Vector Vector::normalize() const {
  double m = mag();
  return Vector(x / m, y / m, z / m);
}

Vector solveScalers(const Vector &v1, const Vector &v2, const Vector &v3,
                    const Vector &C) {
  double denom = v1.z * v2.y * v3.x - v1.y * v2.z * v3.x - v1.z * v2.x * v3.y +
                 v1.x * v2.z * v3.y + v1.y * v2.x * v3.z - v1.x * v2.y * v3.z;
  double a = C.z * v2.y * v3.x - C.y * v2.z * v3.x - C.z * v2.x * v3.y +
             C.x * v2.z * v3.y + C.y * v2.x * v3.z - C.x * v2.y * v3.z;
  double b = -C.z * v1.y * v3.x + C.y * v1.z * v3.x + C.z * v1.x * v3.y -
             C.x * v1.z * v3.y - C.y * v1.x * v3.z + C.x * v1.y * v3.z;
  double c = C.z * v1.y * v2.x - C.y * v1.z * v2.x - C.z * v1.x * v2.y +
             C.x * v1.z * v2.y + C.y * v1.x * v2.z - C.x * v1.y * v2.z;
  return Vector(a / denom, b / denom, c / denom);
}

// Add new optimized version that uses cached values
Vector solveScalersCached(const Vector &C, double cachedDenom,
                          const Vector &coeffsA, const Vector &coeffsB,
                          const Vector &coeffsC) {
  double a = C.x * coeffsA.x + C.y * coeffsA.y + C.z * coeffsA.z;
  double b = C.x * coeffsB.x + C.y * coeffsB.y + C.z * coeffsB.z;
  double c = C.x * coeffsC.x + C.y * coeffsC.y + C.z * coeffsC.z;
  return Vector(a / cachedDenom, b / cachedDenom, c / cachedDenom);
}

Ray::Ray(const Vector &po, const Vector &ve) : point(po), vector(ve) {}
