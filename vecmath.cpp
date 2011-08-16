
#include "vecmath.h"

float rayPlaneIntersection (const Ray& r, const Plane& p) {
	float t = - ((p.normal.dot(r.start) + p.d) / p.normal.dot(r.dir));

	return t;
}

float solve (const Plane& plane, const Vec3f& p) {
	return plane.normal.dot(p)+plane.d;
}

Vec3f solve (const Ray& ray, const float& t) {
	return ray.start + t * ray.dir;
}

bool pointInsideAABB (const AABB& b, const Vec3f& p) {
	// The point has to be inside every plane.
	// That said, this code runs all the planes and if any of them returns bigger than zero, it is outside and returns false.
	for (unsigned int i=0; i<6; ++i) {
		if (solve(b.planes[i], p) > DEFAULT_ERROR) {
			return false;
		}
	}
	return true;
}

Vec3f closestVertex (const Vec3f& p, const AABB& box) {
	// If p.x is at the right, then the right vertex is the closest.
	// if p.x is at the left, then the 

	Vec3f closest;

	closest[0] = (p[0] < box.xyz[0]) ? box.xyz[0] : (p[0] > box.XYZ[0])? box.XYZ[0] : p[0];
	closest[1] = (p[1] < box.xyz[1]) ? box.xyz[1] : (p[1] > box.XYZ[1])? box.XYZ[1] : p[1];
	closest[2] = (p[2] < box.xyz[2]) ? box.xyz[2] : (p[2] > box.XYZ[2])? box.XYZ[2] : p[2];

	return closest;
}

bool collision (const AABB& b, const Ray& r) {
	Vec3f intersection;
	const Vec3f lower = b.xyz - Vec3f (DEFAULT_ERROR, DEFAULT_ERROR, -DEFAULT_ERROR);
	const Vec3f upper = b.XYZ + Vec3f (DEFAULT_ERROR, DEFAULT_ERROR, -DEFAULT_ERROR);
//	const Vec3f lower = b.xyz;
//	const Vec3f upper = b.XYZ;

	for (int i=0; i<6; ++i) {
		float parameter = rayPlaneIntersection (r, b.planes[i]); // returns the t parameter (the value for the ray equation that gives intersection point)

		Vec3f solution = solve(r, parameter); // put the t value above on the plane and returns the intersection point

		if (parameter > -DEFAULT_ERROR &&
			solution[0] >= lower[0] &&
			solution[1] >= lower[1] &&
			solution[2] >= lower[2] &&
			solution[0] <= upper[0] &&
			solution[1] <= upper[1] &&
			solution[2] <= upper[2] ) {

		//	std::cout << "collided! plane = " << b.planes[i] << ", point = " << solution << std::endl;
			return true;
		}
		else {
//			std::cout << "didnt=" << solution << "  ";
		}
	}
//	std::cout << std::endl;
	return false;
}

bool collision (const AABB& b1, const AABB& b2) {//, const float& error = DEFAULT_ERROR) {

//	std::cout << "box1: " << b1.xyz << "    " << b1.XYZ << std::endl;
//	std::cout << "box2: " << b2.xyz << "    " << b2.XYZ << std::endl;


	// Creates vectors (Rays) between the vertices of b2 and tests for ray-box intersection

	const float error = DEFAULT_ERROR;
	const Vec3f xyz = b2.xyz - Vec3f (error, error, error);
	const Vec3f XYZ = b2.XYZ + Vec3f (error, error, error);

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

	Vec3f points[8];
	points[0] = xyz;
	points[1] = XYZ;
	points[2] = Xyz;
	points[3] = xYZ;
	points[4] = xYz;
	points[5] = XyZ;
	points[6] = xyZ;
	points[7] = XYz;

	for (unsigned int i=0; i<8; ++i) {
		if (pointInsideAABB (b1, points[i])) {
			return true;
		}
	}
	return false;
}



Vec3f computeSpheric (float xzRadAngle, float yRadAngle) {
	Vec3f r;
	r[0] = std::sin(yRadAngle)*cos(xzRadAngle);
	r[2] = std::sin(yRadAngle)*sin(xzRadAngle);
	r[1] = std::cos(yRadAngle); // Z third dimension from math is Y while on OpenGL.
	return r;
}


Vec3f abs (const Vec3f& vec) {
	return Vec3f (std::fabs(vec[0]), std::fabs(vec[1]), std::fabs(vec[2]));
}




// vsize is the number of positions of the array, not the number of vertices!!!
void getBorders (float* array, unsigned int vsize, Vec3f& small, Vec3f& big) {
	big = Vec3f (array[0], array[1], array[2]);
	small = Vec3f (array[0], array[1], array[2]);

	for (unsigned int i=3; i<vsize; i+=3) { // 3 because the first is the initial biggest
		for (unsigned int j=0; j<3; ++j) {
			if (array[i+j] > big[j]) {
				big[j] = array[i+j];
			}
			if (array[i+j] < small[j]) {
				small[j] = array[i+j];
			}
		}
	}
}

// Builds an array with only the indexed vertices and calls getBorders
void getIndexedBorders (float* vertexArray, unsigned int* indicesArray, unsigned int isize, Vec3f& small, Vec3f& big) {
	float* indexedVertexArray = new float[isize*3];
	for (unsigned int i=0; i<isize; ++i) {
		indexedVertexArray[0 + 3*i] = vertexArray[0 + 3*indicesArray[i]];
		indexedVertexArray[1 + 3*i] = vertexArray[1 + 3*indicesArray[i]];
		indexedVertexArray[2 + 3*i] = vertexArray[2 + 3*indicesArray[i]];
	}
	getBorders (indexedVertexArray, isize*3, small, big);
	delete indexedVertexArray;
}

Vec3f getCenter (const AABB& b) {
	return ((b.xyz + b.XYZ)/2.0f);
}

Vec3f randomUnitVector () {
	Vec3f v (rand(), rand(), rand());
	return v.normalize();

}

