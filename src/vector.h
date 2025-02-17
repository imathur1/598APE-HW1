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

  inline void operator+=(const Vector &);
  inline void operator-=(const Vector &);
  inline void operator*=(const double);
  inline void operator*=(const float);
  inline void operator*=(const int);
  inline void operator/=(const double);
  inline void operator/=(const float);
  inline void operator/=(const int);

  inline Vector operator+(const Vector &rhs) const {
    return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
  }
  inline Vector operator-(const Vector &rhs) const {
    return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
  }
  /*  Vector operator * (const Vector);*/
  inline Vector operator*(const double rhs) const {
    return Vector(x * rhs, y * rhs, z * rhs);
  }
  inline Vector operator*(const float rhs) const {
    return Vector(x * rhs, y * rhs, z * rhs);
  }
  inline Vector operator*(const int rhs) const {
    return Vector(x * rhs, y * rhs, z * rhs);
  }
  inline Vector operator/(const double rhs) const {
    return Vector(x / rhs, y / rhs, z / rhs);
  }
  inline Vector operator/(const float rhs) const {
    return Vector(x / rhs, y / rhs, z / rhs);
  }
  inline Vector operator/(const int rhs) const {
    return Vector(x / rhs, y / rhs, z / rhs);
  }
  inline Vector cross(const Vector &a) const {
    return Vector(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
  }
  inline double mag2() const { return x * x + y * y + z * z; }
  inline double mag() const { return sqrt(x * x + y * y + z * z); }
  inline double dot(const Vector &a) const {
    return x * a.x + y * a.y + z * a.z;
  }
  inline Vector normalize() const {
    double m = mag();
    return Vector(x / m, y / m, z / m);
  }
};

class Ray {
public:
  Vector point, vector;
  Ray(const Vector &po, const Vector &ve);
};

inline Vector operator-(const Vector &b) { return Vector(-b.x, -b.y, -b.z); }

inline Vector operator+(const Vector &b) { return b; }

inline Vector operator*(const int a, const Vector &b) {
  return Vector(a * b.x, a * b.y, a * b.z);
}

inline Vector operator*(const double a, const Vector &b) {
  return Vector(a * b.x, a * b.y, a * b.z);
}

inline Vector operator*(const float a, const Vector &b) {
  return Vector(a * b.x, a * b.y, a * b.z);
}

inline Vector operator/(const int a, const Vector &b) {
  return Vector(a / b.x, a / b.y, a / b.z);
}

inline Vector operator/(const double a, const Vector &b) {
  return Vector(a / b.x, a / b.y, a / b.z);
}

inline Vector operator/(const float a, const Vector &b) {
  return Vector(a / b.x, a / b.y, a / b.z);
}

inline Vector solveScalersCached(const Vector &C, double cachedDenom,
                                 const Vector &coeffsA, const Vector &coeffsB,
                                 const Vector &coeffsC) {
  double a = C.x * coeffsA.x + C.y * coeffsA.y + C.z * coeffsA.z;
  double b = C.x * coeffsB.x + C.y * coeffsB.y + C.z * coeffsB.z;
  double c = C.x * coeffsC.x + C.y * coeffsC.y + C.z * coeffsC.z;
  return Vector(a / cachedDenom, b / cachedDenom, c / cachedDenom);
}

int print_vector(FILE *stream, const struct printf_info *info,
                 const void *const *args);

int print_vector_arginfo(const struct printf_info *info, size_t n,
                         int *argtypes);

#endif
