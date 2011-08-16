
#ifndef PLANE_H
#define PLANE_H

#include "Vec3f.h"
#include <iostream>


class Plane {
	public:
	Vec3f normal;
	float d;
	
	Plane ();
	Plane (const Vec3f& newn, float newd);

	Plane (const Vec3f& p1, const Vec3f& p2, const Vec3f& p3);

	float solve (const Vec3f& p) const;
};

std::ostream& operator<< (std::ostream& out, const Plane& thePlane);


#endif

