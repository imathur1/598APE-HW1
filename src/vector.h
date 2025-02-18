#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__
#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/ext/vector_double3.hpp>
#include <limits.h>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#define inf std::numeric_limits<double>::infinity()

class Ray {
public:
  glm::dvec3 point, vector;
  Ray(const glm::dvec3 &po, const glm::dvec3 &ve);
};

inline glm::dvec3 solveScalersCached(const glm::dvec3 &C, double cachedDenom,
                                     const glm::dvec3 &coeffsA,
                                     const glm::dvec3 &coeffsB,
                                     const glm::dvec3 &coeffsC) {
  double a = C.x * coeffsA.x + C.y * coeffsA.y + C.z * coeffsA.z;
  double b = C.x * coeffsB.x + C.y * coeffsB.y + C.z * coeffsB.z;
  double c = C.x * coeffsC.x + C.y * coeffsC.y + C.z * coeffsC.z;
  return glm::dvec3(a / cachedDenom, b / cachedDenom, c / cachedDenom);
}

int print_vector(FILE *stream, const struct printf_info *info,
                 const void *const *args);

int print_vector_arginfo(const struct printf_info *info, size_t n,
                         int *argtypes);

#endif
