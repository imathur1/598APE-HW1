#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "shape.h"
#include "vector.h"
#include <glm/ext/vector_double3.hpp>

class Sphere : public Shape {
public:
  double radius;
  Sphere(const glm::dvec3 &c, Texture *t, double ya, double pi, double ro,
         double radius);
  double getIntersection(const Ray &ray) const;
  void move();
  bool getLightIntersection(const Ray &ray, double *fill);
  void getColor(unsigned char *toFill, double *am, double *op, double *ref,
                Autonoma *r, const Ray &ray, unsigned int depth);
  glm::dvec3 getNormal(const glm::dvec3 &point) const;
  unsigned char reversible();
  void setAngles(double a, double b, double c);
  void setYaw(double a);
  void setPitch(double b);
  void setRoll(double c);
};
#endif
