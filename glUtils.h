
#ifndef GLUTILS_H
#define GLUTILS_H

#include <GL/freeglut.h>
#include "AABB.h"
#include "Vec3f.h"
#include "Ray.h"

void draw (const Plane& p);
void drawGeometry (const AABB& b);
void drawGeometry (const Ray& r);


#endif




