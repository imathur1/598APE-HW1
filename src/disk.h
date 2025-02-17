#ifndef __DISK_H__
#define __DISK_H__
#include "plane.h"

class Disk : public Plane {
public:
  Disk(const Vector &c, Texture *t, double ya, double pi, double ro, double tx,
       double ty);
  double getIntersection(const Ray &ray) const;
  bool getLightIntersection(const Ray &ray, double *fill);
};

#endif
