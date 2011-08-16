

#ifndef GLGRID_H
#define GLGRID_H

#include <iostream>
#include "Vec3f.h"
#include "Net.h"
#include "MatrixCoord3D.h"
#include "Terminal.h"

class GLGrid {
	public:
	float *vertexArray;
	unsigned int vertexNumber;
	float color[3];

	GLGrid ();
	~GLGrid ();
	void build (const MatrixCoord3D& start, const MatrixCoord3D& end, const float& yDisplacement, const float& pitch, const float& height);

	void setColor (const Vec3f& c);
};

#endif
