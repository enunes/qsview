
#include "AABB.h"

AABB::AABB () {};

AABB::AABB (const Vec3f& nl, const Vec3f& nh) { // new low, new high
	xyz = nl;
	XYZ = nh;

	Vec3f Xyz = xyz;
	Xyz[0] = XYZ[0];

	Vec3f xYz = xyz;
	xYz[1] = XYZ[1];

	Vec3f xyZ = xyz;
	xyZ[2] = XYZ[2];

	Vec3f xYZ = XYZ;
	xYZ[0] = xyz[0];

	Vec3f XyZ = XYZ;
	XyZ[1] = xyz[1];

	Vec3f XYz = XYZ;
	XYz[2] = xyz[2];

	planes[0] = Plane (xyZ, XyZ, XYZ);
	planes[1] = Plane (Xyz, xyz, xYz);
	planes[2] = Plane (xyz, xyZ, xYZ);
	planes[3] = Plane (XyZ, Xyz, XYz);
	planes[4] = Plane (xYz, xYZ, XYZ);
	planes[5] = Plane (xyz, Xyz, XyZ);

	center = (xyz + XYZ) / 2.0f;
}

std::ostream& operator<< (std::ostream& out, const AABB& theAABB) {
	out << theAABB.xyz << " " << theAABB.XYZ;
	for (unsigned int i=0; i<6; ++i) {
		out << " " << theAABB.planes[i];
	}
	return out;
}

