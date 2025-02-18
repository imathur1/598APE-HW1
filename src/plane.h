#ifndef __PLANE_H__
#define __PLANE_H__

#include "shape.h"
#include "vector.h"
#include <glm/ext/vector_double3.hpp>

class Plane : public Shape {
public:
  glm::dvec3 vect, right, up;
  double d;
  Plane(const glm::dvec3 &c, Texture *t, double ya, double pi, double ro,
        double tx, double ty);
  double getIntersection(const Ray &ray) const;
  bool getLightIntersection(const Ray &ray, double *toFill);
  void move();
  void getColor(unsigned char *toFill, double *am, double *op, double *ref,
                Autonoma *r, const Ray &ray, unsigned int depth);
  glm::dvec3 getNormal(const glm::dvec3 &point) const;
  unsigned char reversible();
  void setAngles(double yaw, double pitch, double roll);
  void setYaw(double d);
  void setPitch(double d);
  void setRoll(double d);
};

#endif
