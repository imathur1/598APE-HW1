#ifndef __BOX_H__
#define __BOX_H__
#include "plane.h"
#include "vector.h"
#include <glm/ext/vector_double3.hpp>

class Box : public Plane {
public:
  Box(const glm::dvec3 &c, Texture *t, double ya, double pi, double ro,
      double tx, double ty);
  Box(const glm::dvec3 &c, Texture *t, double ya, double pi, double ro,
      double tx);
  double getIntersection(const Ray &ray) const;
  bool getLightIntersection(const Ray &ray, double *fill);
};

#endif
