#include "triangle.h"
#include "vector.h"
#include <glm/ext/vector_double3.hpp>
#include <glm/geometric.hpp>
#include <limits>

Triangle::Triangle(const glm::dvec3 &c, const glm::dvec3 &b,
                   const glm::dvec3 &a, Texture *t)
    : Plane(glm::dvec3(0, 0, 0), t, 0., 0., 0., 0., 0.), a(a), b(b), c(c) {
  center = c;
  glm::dvec3 righta = (b - c);
  textureX = glm::length(righta);
  right = righta / textureX;
  vect = glm::normalize(glm::cross(right, b - a));

  xsin = -right.z;
  if (xsin < -1.)
    xsin = -1;
  else if (xsin > 1.)
    xsin = 1.;
  yaw = asin(xsin);
  xcos = sqrt(1. - xsin * xsin);

  zcos = right.x / xcos;
  zsin = -right.y / xcos;
  if (zsin < -1.)
    zsin = -1;
  else if (zsin > 1.)
    zsin = 1.;
  if (zcos < -1.)
    zcos = -1;
  else if (zcos > 1.)
    zcos = 1.;
  roll = asin(zsin);

  ycos = vect.z / xcos;
  if (ycos < -1.)
    ycos = -1;
  else if (ycos > 1.)
    ycos = 1.;
  pitch = acos(ycos);
  ysin = sqrt(1 - ycos * ycos);

  up.x = -xsin * ysin * zcos + ycos * zsin;
  up.y = ycos * zcos + xsin * ysin * zsin;
  up.z = -xcos * ysin;
  glm::dvec3 temp = glm::cross(vect, right);

  updateScalerCache(right, up, vect);
  glm::dvec3 np =
      solveScalersCached(a - c, cachedDenom, coeffsA, coeffsB, coeffsC);
  textureY = np.y;
  thirdX = np.x;

  d = -glm::dot(vect, center);
}

double Triangle::getIntersection(const Ray &ray) const {
  // The Moller-Trumbore algorithm
  constexpr double epsilon = std::numeric_limits<double>::epsilon();
  glm::dvec3 edge1 = b - a;
  glm::dvec3 edge2 = c - a;
  glm::dvec3 ray_cross_e2 = glm::cross(ray.vector, edge2);
  double det = glm::dot(edge1, ray_cross_e2);
  if (det > -epsilon && det < epsilon)
    return inf;
  double inv_det = 1. / det;
  glm::dvec3 s = ray.point - a;
  double u = inv_det * glm::dot(s, ray_cross_e2);
  if ((u < 0.0 && std::abs(u) > epsilon) ||
      (u > 1.0 && std::abs(u - 1.0) > epsilon))
    return inf;

  glm::dvec3 s_cross_e1 = glm::cross(s, edge1);
  double v = inv_det * glm::dot(ray.vector, s_cross_e1);
  if ((v < 0.0 && std::abs(v) > epsilon) ||
      (u + v > 1.0 && std::abs(u + v - 1.0) > epsilon))
    return inf;

  double t = inv_det * glm::dot(edge2, s_cross_e1);
  if (t > epsilon)
    return t;
  else
    return inf;
}

bool Triangle::getLightIntersection(const Ray &ray, double *fill) {
  if (getIntersection(ray) == inf)
    return false;

  const double t = glm::dot(ray.vector, vect);
  const double norm = glm::dot(vect, ray.point) + d;
  const double r = -norm / t;
  if (r <= 0. || r >= 1.)
    return false;
  glm::dvec3 dist = solveScalersCached(ray.point + ray.vector * r - center,
                                       cachedDenom, coeffsA, coeffsB, coeffsC);

  //   unsigned char tmp =
  //       (thirdX - dist.x) * textureY + (thirdX - textureX) * (dist.y -
  //       textureY) < 0.0;
  //   if ((tmp != (textureX * dist.y < 0.0)) ||
  //       (tmp != (dist.x * textureY - thirdX * dist.y < 0.0)))
  //     return false;

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
