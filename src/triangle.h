#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "plane.h"
#include <glm/ext/vector_double3.hpp>

class Triangle : public Plane {
public:
  glm::dvec3 a, b, c;
  double thirdX;
  Triangle(const glm::dvec3 &c, const glm::dvec3 &b, const glm::dvec3 &a,
           Texture *t);
  double getIntersection(const Ray &ray) const;
  bool getLightIntersection(const Ray &ray, double *fill);
};

#endif
