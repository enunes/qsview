
#ifndef GLWEB_H
#define GLWEB_H

#include <iostream>
#include "Vec3f.h"
#include "Net.h"
#include "MatrixCoord3D.h"
#include "Terminal.h"

class GLWeb {
	public:
	float *vertexArray;
	unsigned int vertexNumber;
	float color[3];
	unsigned int width;


	GLWeb ();
	~GLWeb ();
	void build (const Net& n, const std::vector<Terminal>& terminalList, const float& pitch, const float& height);
	void setWidth (const unsigned int& newWidth);
	void setColor (const Vec3f& c);
};

std::ostream& operator<< (std::ostream& out, const GLWeb& glw);

#endif
