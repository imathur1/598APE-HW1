#ifndef __DISK_H__
#define __DISK_H__
#include "plane.h"
#include "vector.h"
#include <glm/ext/vector_double3.hpp>

class Disk : public Plane {
public:
  Disk(const glm::dvec3 &c, Texture *t, double ya, double pi, double ro,
       double tx, double ty);
  double getIntersection(const Ray &ray) const;
  bool getLightIntersection(const Ray &ray, double *fill);
};

#endif
