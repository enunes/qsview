
#include "GLWeb.h"

GLWeb::GLWeb () {
	vertexArray = NULL;
}

GLWeb::~GLWeb () {
	delete [] vertexArray;
}

void GLWeb::build (const Net& n, const std::vector<Terminal>& terminalList, const float& pitch, const float& height) {
	std::vector<Vec3f> vertices;

	for (unsigned int i=0; i<n.terminals.size()-1; ++i) {
		for (unsigned int j=i+1; j<n.terminals.size(); ++j) {
			const MatrixCoord3D& c1 = terminalList[n.terminals[i]].coord;
			const MatrixCoord3D& c2 = terminalList[n.terminals[j]].coord;

			const Vec3f v1 = Vec3f (static_cast<float>(c1[0])*pitch, static_cast<float>(c1[2])*height, static_cast<float>(c1[1])*pitch);
			const Vec3f v2 = Vec3f (static_cast<float>(c2[0])*pitch, static_cast<float>(c2[2])*height, static_cast<float>(c2[1])*pitch);

			vertices.push_back (v1);
			vertices.push_back (v2);
		}
	}

	vertexNumber = vertices.size();
	vertexArray = new float[3*vertices.size()];

	for (unsigned int i=0; i<vertices.size(); ++i) {
		vertexArray[i*3] = vertices[i][0];
		vertexArray[i*3+1] = vertices[i][1];
		vertexArray[i*3+2] = -vertices[i][2];
	}
}

void GLWeb::setColor (const Vec3f& c) {
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
}

void GLWeb::setWidth (const unsigned int& newWidth) {
	width = newWidth;
}

std::ostream& operator<< (std::ostream& out, const GLWeb& glw) {
	out << glw.color;
	return out;
}
