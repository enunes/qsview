
#ifndef RAY_H
#define RAY_H

#include "Vec3f.h"

class Ray {
	public:
	Vec3f start, dir;

	Ray ();

	Ray (const Vec3f& nstart, const Vec3f& ndir);
};


#endif


