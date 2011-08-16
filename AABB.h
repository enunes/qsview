
#ifndef AABB_H
#define AABB_H

#include "Vec3f.h"
#include "Plane.h"


class AABB {
	public:
	Vec3f xyz;
	Vec3f center;
	Vec3f XYZ;
	Plane planes[6]; // top, bottom, right, left, front, back

	AABB ();

	AABB (const Vec3f& nl, const Vec3f& nh); 

};

std::ostream& operator<< (std::ostream& out, const AABB& theAABB);


#endif

