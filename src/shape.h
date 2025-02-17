#ifndef __SHAPE_H__
#define __SHAPE_H__
#include "light.h"
#include "vector.h"

class Shape {
public:
  Shape(const Vector &c, Texture *t, double ya, double pi, double ro);
  double yaw, pitch, roll, xsin, xcos, ysin, ycos, zsin, zcos;
  Vector center;
  Texture *texture;
  double textureX, textureY, mapX, mapY, mapOffX, mapOffY;
  Texture *normalMap;
  virtual double getIntersection(const Ray &ray) const = 0;
  virtual bool getLightIntersection(const Ray &ray, double *fill) = 0;
  virtual void move() = 0;
  virtual unsigned char reversible() = 0;
  virtual void getColor(unsigned char *toFill, double *am, double *op,
                        double *ref, Autonoma *r, const Ray &ray,
                        unsigned int depth) = 0;
  virtual Vector getNormal(const Vector &point) const = 0;
  virtual void setAngles(double yaw, double pitch, double roll) = 0;
  virtual void setYaw(double d) = 0;
  virtual void setPitch(double d) = 0;
  virtual void setRoll(double d) = 0;

protected:
  // Add cached values for solveScalers
  double cachedDenom;
  Vector coeffsA, coeffsB, coeffsC;

  // Helper to update cached values
  void updateScalerCache(const Vector &right, const Vector &up,
                         const Vector &vect) {
    // right = v1, up = v2, vect = v3
    cachedDenom = right.z * up.y * vect.x - right.y * up.z * vect.x -
                  right.z * up.x * vect.y + right.x * up.z * vect.y +
                  right.y * up.x * vect.z - right.x * up.y * vect.z;

    // Pre-compute coefficients for a
    coeffsA.x = up.z * vect.y - up.y * vect.z;
    coeffsA.y = -up.z * vect.x + up.x * vect.z;
    coeffsA.z = up.y * vect.x - up.x * vect.y;

    // Pre-compute coefficients for b
    coeffsB.x = -right.z * vect.y + right.y * vect.z;
    coeffsB.y = right.z * vect.x - right.x * vect.z;
    coeffsB.z = -right.y * vect.x + right.x * vect.y;

    // Pre-compute coefficients for c
    coeffsC.x = right.z * up.y - right.y * up.z;
    coeffsC.y = -right.z * up.x + right.x * up.z;
    coeffsC.z = right.y * up.x - right.x * up.y;
  }
};

void calcColor(unsigned char *toFill, Autonoma *, const Ray &ray,
               unsigned int depth);

#endif
