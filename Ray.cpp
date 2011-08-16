
#include "Ray.h"

Ray::Ray () {
}

Ray::Ray (const Vec3f& nstart, const Vec3f& ndir) {
	start = nstart;
	dir = ndir;
}

