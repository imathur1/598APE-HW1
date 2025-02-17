#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits.h>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#define inf std::numeric_limits<double>::infinity()

class Vector {
public:
  double x, y, z;
  Vector() : x(0.0), y(0.0), z(0.0) {}
  Vector(double a, double b, double c);

  void operator+=(const Vector &);
  void operator-=(const Vector &);
  void operator*=(const double);
  void operator*=(const float);
  void operator*=(const int);
  void operator/=(const double);
  void operator/=(const float);
  void operator/=(const int);

  Vector operator+(const Vector &) const;
  Vector operator-(const Vector &) const;
  /*  Vector operator * (const Vector);*/
  Vector operator*(const double) const;
  Vector operator*(const float) const;
  Vector operator*(const int) const;
  Vector operator/(const double) const;
  Vector operator/(const float) const;
  Vector operator/(const int) const;
  Vector cross(const Vector &a) const;
  double mag2() const;
  double mag() const;
  double dot(const Vector &a) const;
  Vector normalize() const;
};

class Ray {
public:
  Vector point, vector;
  Ray(const Vector &po, const Vector &ve);
};

inline Vector operator-(const Vector b) { return Vector(-b.x, -b.y, -b.z); }

inline Vector operator+(const Vector b) { return b; }

inline Vector operator*(const int a, const Vector b) {
  return Vector(a * b.x, a * b.y, a * b.z);
}

inline Vector operator*(const double a, const Vector b) {
  return Vector(a * b.x, a * b.y, a * b.z);
}

inline Vector operator*(const float a, const Vector b) {
  return Vector(a * b.x, a * b.y, a * b.z);
}

inline Vector operator/(const int a, const Vector b) {
  return Vector(a / b.x, a / b.y, a / b.z);
}

inline Vector operator/(const double a, const Vector b) {
  return Vector(a / b.x, a / b.y, a / b.z);
}

inline Vector operator/(const float a, const Vector b) {
  return Vector(a / b.x, a / b.y, a / b.z);
}

Vector solveScalers(const Vector &v1, const Vector &v2, const Vector &v3,
                    const Vector &solve);

Vector solveScalersCached(const Vector &C, double cachedDenom,
                          const Vector &coeffsA, const Vector &coeffsB,
                          const Vector &coeffsC);

int print_vector(FILE *stream, const struct printf_info *info,
                 const void *const *args);

int print_vector_arginfo(const struct printf_info *info, size_t n,
                         int *argtypes);

#endif
