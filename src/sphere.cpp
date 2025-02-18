#include "sphere.h"
#include "vector.h"
#include <glm/ext/vector_double3.hpp>
#include <glm/geometric.hpp>
// #include <glm/gtx/norm.hpp>

namespace glm {
double length2(const glm::dvec3 &v) { return dot(v, v); }
}; // namespace glm

Sphere::Sphere(const glm::dvec3 &c, Texture *t, double ya, double pi, double ro,
               double rad)
    : Shape(c, t, ya, pi, ro) {
  textureX = textureY = 1.;
  normalMap = NULL;
  radius = rad;
}
bool Sphere::getLightIntersection(const Ray &ray, double *fill) {
  const double A = glm::length2(ray.vector);
  const double B = 2 * glm::dot(ray.vector, ray.point - center);
  const double C = glm::length2(ray.point - center) - radius * radius;
  const double descriminant = B * B - 4 * A * C;
  if (descriminant < 0. || descriminant < B * ((B >= 0) ? B : -B))
    return false;

  const double desc = sqrt(descriminant);
  const double root1 = (-B - desc) / (2 * A);
  const double root2 = (-B + desc) / (2 * A);
  const double time = (root1 > 0) ? root1 : root2;
  if (time >= 1.)
    return false;
  glm::dvec3 point = ray.point + ray.vector * time;
  double data2 = (center.y - point.y + radius) / (2 * radius);
  double data3 = atan2(point.z - center.z, point.x - center.x);
  unsigned char temp[4];
  double amb, op, ref;
  texture->getColor(temp, &amb, &op, &ref,
                    fix((yaw + data2) / M_TWO_PI / textureX),
                    fix((pitch / M_TWO_PI - (data3))) / textureY);
  if (op > 1 - 1E-6)
    return true;
  fill[0] *= temp[0] / 255.;
  fill[1] *= temp[1] / 255.;
  fill[2] *= temp[2] / 255.;
  return false;
}
double Sphere::getIntersection(const Ray &ray) const {
  const double A = glm::length2(ray.vector);
  const double B = 2 * glm::dot(ray.vector, ray.point - center);
  const double C = glm::length2(ray.point - center) - radius * radius;
  const double descriminant = B * B - 4 * A * C;
  if (descriminant < 0)
    return inf;
  else {
    const double desc = sqrt(descriminant);
    const double root1 = (-B - desc) / (2 * A);
    const double root2 = (-B + desc) / (2 * A);
    return (root1 > 0) ? (root1) : ((root2 > 0) ? root2 : inf);
  }
}
void Sphere::move() { return; }
unsigned char Sphere::reversible() { return 0; }

void Sphere::getColor(unsigned char *toFill, double *amb, double *op,
                      double *ref, Autonoma *r, const Ray &ray,
                      unsigned int depth) {
  double data3 = (center.y - ray.point.y + radius) / (2 * radius);
  double data2 = atan2(ray.point.z - center.z, ray.point.x - center.x);
  texture->getColor(toFill, amb, op, ref,
                    fix((yaw + data2) / M_TWO_PI / textureX),
                    fix((pitch / M_TWO_PI - (data3)) / textureY));
}
glm::dvec3 Sphere::getNormal(const glm::dvec3 &point) const {
  glm::dvec3 vect = point - center;
  /*   A x B = <x, y, z>
  <ay bz- az by,  bz ax - az bx, ax by - bx ay>
  az = 0

  <ay bz,  bz ax, ax by - bx ay >

  bx = 0

  <ay bz,  bz ax, ax by >

  ax = 1

  <ay bz,  bz , by >

  B: <0, z, -y>
  A <-1,x/y,0>
  */
  if (normalMap == NULL)
    return vect;
  double data3 = (center.y - point.y + radius) / (2 * radius);
  double data2 = atan2(point.z - center.z, point.x - center.x);
  vect = glm::normalize(vect);
  glm::dvec3 right = glm::dvec3(vect.x, vect.z, -vect.y);
  glm::dvec3 up = glm::dvec3(vect.z, vect.y, -vect.x);
  double am, ref, op;
  unsigned char norm[3];
  normalMap->getColor(norm, &am, &op, &ref,
                      fix(((mapOffX + mapOffX) + data2) / M_TWO_PI / mapX),
                      fix(((mapOffY + mapOffY) / M_TWO_PI - data3) / mapY));
  return glm::normalize((norm[0] - 128.0) * right + (norm[1] - 128.0) * up +
                        (norm[2] * 1.0) * vect);
}

void Sphere::setAngles(double a, double b, double c) {
  yaw = a;
  pitch = b;
  roll = c;
  xcos = cos(yaw);
  xsin = sin(yaw);
  ycos = cos(pitch);
  ysin = sin(pitch);
  zcos = cos(roll);
  zsin = sin(roll);
}

void Sphere::setYaw(double a) {
  yaw = a;
  xcos = cos(yaw);
  xsin = sin(yaw);
}

void Sphere::setPitch(double b) {
  pitch = b;
  ycos = cos(pitch);
  ysin = sin(pitch);
}

void Sphere::setRoll(double c) {
  roll = c;
  zcos = cos(roll);
  zsin = sin(roll);
}