
#ifndef GLSEGMENT_H
#define GLSEGMENT_H

#include <iostream>
#include "Vec3f.h"
#include "Segment.h"

class GLSegment {
	public:
//	float vertexArray[108]; // 6 * 2 * 3 * 3, 6 faces, 2 triangles per face, 3 vertices per triangle, 3 floats per vertice
//	float color[3];
	unsigned int ind[12*3];

	GLSegment ();
};

std::ostream& operator<< (std::ostream& out, const GLSegment& gls);

#endif
