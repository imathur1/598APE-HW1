#include <limits>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <printf.h>
#include "vector.h"
#include <glm/ext/vector_double3.hpp>
#include <stddef.h>

Ray::Ray(const glm::dvec3 &po, const glm::dvec3 &ve) : point(po), vector(ve) {}
