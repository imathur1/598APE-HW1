#include "triangle.h"
#include "vector.h"
#include <limits>

Triangle::Triangle(const Vector &c, const Vector &b, const Vector &a,
                   Texture *t)
    : Plane(Vector(0, 0, 0), t, 0., 0., 0., 0., 0.), a(a), b(b), c(c) {
  center = c;
  Vector righta = (b - c);
  textureX = righta.mag();
  right = righta / textureX;
  vect = right.cross(b - a).normalize();

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
  Vector temp = vect.cross(right);

  updateScalerCache(right, up, vect);
  Vector np = solveScalersCached(a - c, cachedDenom, coeffsA, coeffsB, coeffsC);
  textureY = np.y;
  thirdX = np.x;

  d = -vect.dot(center);
}

double Triangle::getIntersection(const Ray &ray) const {
  // The Moller-Trumbore algorithm
  constexpr double epsilon = std::numeric_limits<double>::epsilon();
  Vector edge1 = b - a;
  Vector edge2 = c - a;
  Vector ray_cross_e2 = ray.vector.cross(edge2);
  double det = edge1.dot(ray_cross_e2);
  if (det > -epsilon && det < epsilon)
    return inf;
  double inv_det = 1. / det;
  Vector s = ray.point - a;
  double u = inv_det * s.dot(ray_cross_e2);
  if ((u < 0.0 && std::abs(u) > epsilon) ||
      (u > 1.0 && std::abs(u - 1.0) > epsilon))
    return inf;

  Vector s_cross_e1 = s.cross(edge1);
  double v = inv_det * ray.vector.dot(s_cross_e1);
  if ((v < 0.0 && std::abs(v) > epsilon) ||
      (u + v > 1.0 && std::abs(u + v - 1.0) > epsilon))
    return inf;

  double t = inv_det * edge2.dot(s_cross_e1);
  if (t > epsilon)
    return t;
  else
    return inf;
}

bool Triangle::getLightIntersection(const Ray &ray, double *fill) {
  if (getIntersection(ray) == inf)
    return false;

  const double t = ray.vector.dot(vect);
  const double norm = vect.dot(ray.point) + d;
  const double r = -norm / t;
  if (r <= 0. || r >= 1.)
    return false;
  Vector dist = solveScalersCached(ray.point + ray.vector * r - center,
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
