#include "box.h"
#include "vector.h"
#include <glm/ext/vector_double3.hpp>
#include <glm/geometric.hpp>

Box::Box(const glm::dvec3 &c, Texture *t, double ya, double pi, double ro,
         double tx, double ty)
    : Plane(c, t, ya, pi, ro, tx, ty) {}
Box::Box(const glm::dvec3 &c, Texture *t, double ya, double pi, double ro,
         double tx)
    : Plane(c, t, ya, pi, ro, tx, tx) {}

double Box::getIntersection(const Ray &ray) const {
  double time = Plane::getIntersection(ray);
  glm::dvec3 dist = solveScalersCached(ray.point + ray.vector * time - center,
                                       cachedDenom, coeffsA, coeffsB, coeffsC);
  if (time == inf)
    return time;
  return (((dist.x >= 0) ? dist.x : -dist.x) > textureX / 2 ||
          ((dist.y >= 0) ? dist.y : -dist.y) > textureY / 2)
             ? inf
             : time;
}

bool Box::getLightIntersection(const Ray &ray, double *fill) {
  const double t = glm::dot(ray.vector, vect);
  const double norm = glm::dot(vect, ray.point) + d;
  const double r = -norm / t;
  if (r <= 0. || r >= 1.)
    return false;
  glm::dvec3 dist = solveScalersCached(ray.point + ray.vector * r - center,
                                       cachedDenom, coeffsA, coeffsB, coeffsC);
  if (((dist.x >= 0) ? dist.x : -dist.x) > textureX / 2 ||
      ((dist.y >= 0) ? dist.y : -dist.y) > textureY / 2)
    return false;

  if (texture->opacity > 1 - 1E-6)
    return true;
  unsigned char temp[4];
  double amb, op, ref;
  texture->getColor(temp, &amb, &op, &ref, fix(dist.x / textureX - .5),
                    fix(dist.y / textureY - .5));
  if (op > 1 - 1E-6)
    return true;
  fill[0] *= temp[0] / 255.;
  fill[1] *= temp[1] / 255.;
  fill[2] *= temp[2] / 255.;
  return false;
}