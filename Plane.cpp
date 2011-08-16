
#include "Plane.h"

Plane::Plane() {};
Plane::Plane (const Vec3f& newn, float newd) {
	normal = newn;
	d = newd;
}

Plane::Plane (const Vec3f& p1, const Vec3f& p2, const Vec3f& p3) {
	const Vec3f c1 = p1 - p3;
	const Vec3f c2 = p2 - p1;

	normal = c1.cross(c2).normalize();

	d = -normal.dot(p3);
}

float Plane::solve (const Vec3f& p) const {
	return normal.dot(p)+d;
}

std::ostream& operator<< (std::ostream& out, const Plane& thePlane) {
	out << thePlane.normal << " " << thePlane.d;
	return out;
}


