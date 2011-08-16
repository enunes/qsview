
#include "glUtils.h"

static const Vec3f geometryColor (0.1f, 0.1f, 0.1f);

void draw (const Plane& p) {
	Vec3f point = (-p.d)*p.normal;
	Vec3f line = point + p.normal;
	glColor3f (geometryColor[0], geometryColor[1], geometryColor[2]);
	glPointSize (4);
	glBegin (GL_POINTS);
	glVertex3f (point[0], point[1], point[2]);
	glEnd();
	glBegin (GL_LINES);
	glVertex3f (point[0], point[1], point[2]);
	glVertex3f (line[0], line[1], line[2]);
	glEnd();
}

void drawGeometry (const AABB& b) {

	Vec3f xyz = b.xyz;
	Vec3f XYZ = b.XYZ;

	Vec3f Xyz = b.xyz;
	Xyz[0] = XYZ[0];

	Vec3f xYz = b.xyz;
	xYz[1] = XYZ[1];

	Vec3f xyZ = b.xyz;
	xyZ[2] = XYZ[2];

	Vec3f xYZ = b.XYZ;
	xYZ[0] = xyz[0];

	Vec3f XyZ = b.XYZ;
	XyZ[1] = xyz[1];

	Vec3f XYz = b.XYZ;
	XYz[2] = xyz[2];

	glBegin (GL_LINES);

	glVertex3f (xyz[0], xyz[1], xyz[2]);
	glVertex3f (Xyz[0], Xyz[1], Xyz[2]);

	glVertex3f (xyz[0], xyz[1], xyz[2]);
	glVertex3f (xYz[0], xYz[1], xYz[2]);

	glVertex3f (xyz[0], xyz[1], xyz[2]);
	glVertex3f (xyZ[0], xyZ[1], xyZ[2]);

	glVertex3f (Xyz[0], Xyz[1], Xyz[2]);
	glVertex3f (XYz[0], XYz[1], XYz[2]);

	glVertex3f (Xyz[0], Xyz[1], Xyz[2]);
	glVertex3f (XyZ[0], XyZ[1], XyZ[2]);

	glVertex3f (xyZ[0], xyZ[1], xyZ[2]);
	glVertex3f (xYZ[0], xYZ[1], xYZ[2]);

	glVertex3f (xYz[0], xYz[1], xYz[2]);
	glVertex3f (xYZ[0], xYZ[1], xYZ[2]);

	glVertex3f (xYz[0], xYz[1], xYz[2]);
	glVertex3f (XYz[0], XYz[1], XYz[2]);

	glVertex3f (xyZ[0], xyZ[1], xyZ[2]);
	glVertex3f (XyZ[0], XyZ[1], XyZ[2]);

	glVertex3f (XYz[0], XYz[1], XYz[2]);
	glVertex3f (XYZ[0], XYZ[1], XYZ[2]);

	glVertex3f (xYZ[0], xYZ[1], xYZ[2]);
	glVertex3f (XYZ[0], XYZ[1], XYZ[2]);

	glVertex3f (XyZ[0], XyZ[1], XyZ[2]);
	glVertex3f (XYZ[0], XYZ[1], XYZ[2]);

	glEnd();
}

void drawGeometry (const Ray& r) {
	glBegin (GL_LINES);
	glColor3f (geometryColor[0], geometryColor[1], geometryColor[2]);
	glVertex3f (r.start[0], r.start[1], r.start[2]);
	glColor3f (geometryColor[0], 1.0f-geometryColor[1], 1.0f-geometryColor[2]);
	glVertex3f (r.start[0]+r.dir[0], r.start[1]+r.dir[1], r.start[2]+r.dir[2]);
	glEnd();
}

