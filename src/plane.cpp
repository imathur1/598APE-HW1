#include "plane.h"
#include "vector.h"
#include <glm/ext/vector_double3.hpp>
#include <glm/geometric.hpp>

Plane::Plane(const glm::dvec3 &c, Texture *t, double ya, double pi, double ro,
             double tx, double ty)
    : Shape(c, t, ya, pi, ro), vect(c), right(c), up(c) {
  textureX = tx;
  textureY = ty;
  setAngles(yaw, pitch, roll);
  normalMap = NULL;
  mapX = textureX;
  mapY = textureY;
  updateScalerCache(right, up, vect);
}

void Plane::setAngles(double a, double b, double c) {
  yaw = a;
  pitch = b;
  roll = c;
  xcos = cos(yaw);
  xsin = sin(yaw);
  ycos = cos(pitch);
  ysin = sin(pitch);
  zcos = cos(roll);
  zsin = sin(roll);
  vect.x = xsin * ycos * zcos + ysin * zsin;
  vect.y = ysin * zcos - xsin * ycos * zsin;
  vect.z = xcos * ycos;
  up.x = -xsin * ysin * zcos + ycos * zsin;
  up.y = ycos * zcos + xsin * ysin * zsin;
  up.z = -xcos * ysin;
  right.x = xcos * zcos;
  right.y = -xcos * zsin;
  right.z = -xsin;
  d = -glm::dot(vect, center);
}

void Plane::setYaw(double a) {
  yaw = a;
  xcos = cos(yaw);
  xsin = sin(yaw);

  vect.x = xsin * ycos * zcos + ysin * zsin;
  vect.y = ysin * zcos - xsin * ycos * zsin;
  vect.z = xcos * ycos;
  up.x = -xsin * ysin * zcos + ycos * zsin;
  up.y = ycos * zcos + xsin * ysin * zsin;
  up.z = -xcos * ysin;
  right.x = xcos * zcos;
  right.y = -xcos * zsin;
  right.z = -xsin;
  d = -glm::dot(vect, center);
}

void Plane::setPitch(double b) {
  pitch = b;
  ycos = cos(pitch);
  ysin = sin(pitch);
  vect.x = xsin * ycos * zcos + ysin * zsin;
  vect.y = ysin * zcos - xsin * ycos * zsin;
  vect.z = xcos * ycos;
  up.x = -xsin * ysin * zcos + ycos * zsin;
  up.y = ycos * zcos + xsin * ysin * zsin;
  up.z = -xcos * ysin;
  d = -glm::dot(vect, center);
}

void Plane::setRoll(double c) {
  roll = c;
  zcos = cos(roll);
  zsin = sin(roll);
  vect.x = xsin * ycos * zcos + ysin * zsin;
  vect.y = ysin * zcos - xsin * ycos * zsin;
  //   vect.z = xcos*ycos;
  up.x = -xsin * ysin * zcos + ycos * zsin;
  up.y = ycos * zcos + xsin * ysin * zsin;
  // up.z = -xcos*ysin;
  right.x = xcos * zcos;
  right.y = -xcos * zsin;
  // right.z = -xsin;
  d = -glm::dot(vect, center);
}

double Plane::getIntersection(const Ray &ray) const {
  const double t = glm::dot(ray.vector, vect);
  const double norm = glm::dot(vect, ray.point) + d;
  const double r = -norm / t;
  return (r > 0) ? r : inf;
}

bool Plane::getLightIntersection(const Ray &ray, double *fill) {
  const double t = glm::dot(ray.vector, vect);
  const double norm = glm::dot(vect, ray.point) + d;
  const double r = -norm / t;
  if (r <= 0. || r >= 1.)
    return false;

  if (texture->opacity > 1 - 1E-6)
    return true;
  glm::dvec3 dist = solveScalersCached(ray.point + ray.vector * r - center,
                                       cachedDenom, coeffsA, coeffsB, coeffsC);
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

void Plane::move() { d = -glm::dot(vect, center); }
void Plane::getColor(unsigned char *toFill, double *am, double *op, double *ref,
                     Autonoma *r, const Ray &ray, unsigned int depth) {
  glm::dvec3 dist = solveScalersCached(ray.point - center, cachedDenom, coeffsA,
                                       coeffsB, coeffsC);
  texture->getColor(toFill, am, op, ref, fix(dist.x / textureX - .5),
                    fix(dist.y / textureY - .5));
}
unsigned char Plane::reversible() { return 1; }

glm::dvec3 Plane::getNormal(const glm::dvec3 &point) const {
  if (normalMap == NULL)
    return vect;
  else {
    glm::dvec3 dist = solveScalersCached(point - center, cachedDenom, coeffsA,
                                         coeffsB, coeffsC);
    double am, ref, op;
    unsigned char norm[3];
    normalMap->getColor(norm, &am, &op, &ref, fix(dist.x / mapX - .5 + mapOffX),
                        fix(dist.y / mapY - .5 + mapOffY));
    glm::dvec3 ret =
        glm::normalize((norm[0] - 128.0) * right + (norm[1] - 128.0) * up +
                       (norm[2] * 1.0) * vect);
    return ret;
  }
}