#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <glm/ext/vector_double3.hpp>

class Camera {
public:
  glm::dvec3 focus, right, up, forward;
  double xcos, xsin, ycos, ysin, zcos, zsin;
  Camera(const glm::dvec3 &cente);

  Camera(const glm::dvec3 &f, double a, double b, double c);

  void setAngles(double a, double b, double c);
  void setYaw(double a);
  void setPitch(double a);
  void setRoll(double b);

private:
  double yaw, pitch, roll;
};

#endif
