#ifndef __LIGHT_H__
#define __LIGHT_H__
#include "Textures/colortexture.h"
#include "Textures/texture.h"
#include "camera.h"
#include "vector.h"
#include <vector>

class Light {
public:
  unsigned char *color;
  unsigned char *getColor(unsigned char a, unsigned char b, unsigned char c);
  Vector center;
  Light(const Vector &cente, unsigned char *colo);
};

struct LightNode {
  Light *data;
  LightNode *prev, *next;
};

class Shape;

class Autonoma {
public:
  Camera camera;
  Texture *skybox;
  unsigned int depth;
  std::vector<Shape *> shapes;
  LightNode *lightStart, *lightEnd;
  Autonoma(const Camera &c);
  Autonoma(const Camera &c, Texture *tex);
  void addShape(Shape *s);
  void addLight(Light *s);
  void removeLight(LightNode *s);
};

void getLight(double *toFill, Autonoma *aut, const Vector &point,
              const Vector &norm, unsigned char r);

#endif