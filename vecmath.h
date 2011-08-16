
#ifndef VECMATH_H
#define VECMATH_H

// Put here stuff that uses my Vector, Matrix, Plane, etc classes and don't use OpenGL.

#include <cmath>
#include <cstdlib>
#include "Plane.h"
#include "Vec3f.h"
#include "Ray.h"
#include "AABB.h"

#define DEFAULT_ERROR 0.01f

float rayPlaneIntersection (const Ray& r, const Plane& p);
float solve (const Plane& plane, const Vec3f& p);
Vec3f solve (const Ray& ray, const float& t); 
bool pointInsideAABB (const AABB& b, const Vec3f& p);
Vec3f closestVertex (const Vec3f& p, const AABB& box); 
bool collision (const AABB& b, const Ray& r); 
bool collision (const AABB& b1, const AABB& b2);
Vec3f computeSpheric (float xzRadAngle, float yRadAngle); 
Vec3f abs (const Vec3f& vec); 
void getBorders (float* array, unsigned int vsize, Vec3f& small, Vec3f& big); 
void getIndexedBorders (float* vertexArray, unsigned int* indicesArray, unsigned int isize, Vec3f& small, Vec3f& big); 
Vec3f getCenter (const AABB& b); 
Vec3f randomUnitVector (); 

#endif

