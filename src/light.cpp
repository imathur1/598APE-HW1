#include "light.h"
#include "camera.h"
#include "shape.h"
#include "Textures/texture.h"
#include "vector.h"
#include <glm/ext/vector_double3.hpp>
#include <glm/geometric.hpp>

const unsigned char MAX_COLOR_VALUE = 255.;

Light::Light(const glm::dvec3 &cente, unsigned char *colo) : center(cente) {
  color = colo;
}

unsigned char *Light::getColor(unsigned char a, unsigned char b,
                               unsigned char c) {
  unsigned char *r = (unsigned char *)malloc(sizeof(unsigned char) * 3);
  r[0] = a;
  r[1] = b;
  r[2] = c;
  return r;
}

Autonoma::Autonoma(const Camera &c) : camera(c) {
  shapes.reserve(100);
  lightStart = NULL;
  lightEnd = NULL;
  depth = 10;
  skybox = BLACK;
}

Autonoma::Autonoma(const Camera &c, Texture *tex) : camera(c) {
  shapes.reserve(100);
  lightStart = NULL;
  lightEnd = NULL;
  depth = 10;
  skybox = tex;
}

void Autonoma::addShape(Shape *r) { shapes.push_back(r); }

void Autonoma::addLight(Light *r) {
  LightNode *hi = (LightNode *)malloc(sizeof(LightNode));
  hi->data = r;
  hi->next = hi->prev = NULL;
  if (lightStart == NULL) {
    lightStart = lightEnd = hi;
  } else {
    lightEnd->next = hi;
    hi->prev = lightEnd;
    lightEnd = hi;
  }
}

void Autonoma::removeLight(LightNode *s) {
  if (s == lightStart) {
    if (s == lightEnd) {
      lightStart = lightStart = NULL;
    } else {
      lightStart = s->next;
      lightStart->prev = NULL;
    }
  } else if (s == lightEnd) {
    lightEnd = s->prev;
    lightEnd->next = NULL;
  } else {
    LightNode *b4 = s->prev, *aft = s->next;
    b4->next = aft;
    aft->prev = b4;
  }
  free(s);
}

void getLight(double *tColor, Autonoma *aut, const glm::dvec3 &point,
              const glm::dvec3 &norm, unsigned char flip) {
  double normMag = glm::length(norm);
  tColor[0] = tColor[1] = tColor[2] = 0.;
  LightNode *t = aut->lightStart;
  double lightColor[3];
  while (t != NULL) {

    lightColor[0] = t->data->color[0] / MAX_COLOR_VALUE;
    lightColor[1] = t->data->color[1] / MAX_COLOR_VALUE;
    lightColor[2] = t->data->color[2] / MAX_COLOR_VALUE;
     glm::dvec3 ra = t->data->center - point;

    bool hit = false;
    const Ray &ray = Ray(point + ra * .01, ra);
    for (Shape *shape : aut->shapes) {
      if (shape->getLightIntersection(ray, lightColor)) {
        hit = true;
        break;
      }
    }

    if (!hit) {
      double perc = (glm::dot(norm, ra) / (glm::length(ra) * normMag));    
      if (perc < 0 && flip)
        perc = -perc;
      if (perc > 0) {
        tColor[0] += perc * (lightColor[0]);
        tColor[1] += perc * (lightColor[0]);
        tColor[2] += perc * (lightColor[0]);
        tColor[0] = fmin(tColor[0], 1.0);
        tColor[1] = fmin(tColor[1], 1.0);
        tColor[2] = fmin(tColor[2], 1.0);
      }
    }
    t = t->next;
  }
}