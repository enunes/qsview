
#include "GLGrid.h"

GLGrid::GLGrid () {
	vertexArray = NULL;
}

GLGrid::~GLGrid () {
	delete [] vertexArray;
}

// yDisplacement will be used as raw! (bad?)
// y is for OpenGL y
void GLGrid::build (const MatrixCoord3D& start, const MatrixCoord3D& end, const float& yDisplacement, const float& pitch, const float& height) {
	std::vector<Vec3f> vertices;

	for (int i=start[0]; i<=end[0]; ++i) {
		const MatrixCoord3D& c1 = MatrixCoord3D (i, start[1], 0);
		const MatrixCoord3D& c2 = MatrixCoord3D (i, end[1], 0);

		Vec3f v1 = Vec3f (static_cast<float>(c1[0])*pitch, yDisplacement, static_cast<float>(c1[1])*pitch);
		Vec3f v2 = Vec3f (static_cast<float>(c2[0])*pitch, yDisplacement, static_cast<float>(c2[1])*pitch);

		v1 -= Vec3f (pitch/2.0f, 0.0f, pitch/2.0f);
		v2 -= Vec3f (pitch/2.0f, 0.0f, pitch/2.0f);

		vertices.push_back (v1);
		vertices.push_back (v2);
	}

	for (int j=start[1]; j<=end[1]; ++j) {
		const MatrixCoord3D& c1 = MatrixCoord3D (start[0], j, 0);
		const MatrixCoord3D& c2 = MatrixCoord3D (end[0], j, 0);

		Vec3f v1 = Vec3f (static_cast<float>(c1[0])*pitch, yDisplacement, static_cast<float>(c1[1])*pitch);
		Vec3f v2 = Vec3f (static_cast<float>(c2[0])*pitch, yDisplacement, static_cast<float>(c2[1])*pitch);

		v1 -= Vec3f (pitch/2.0f, 0.0f, pitch/2.0f);
		v2 -= Vec3f (pitch/2.0f, 0.0f, pitch/2.0f);

		vertices.push_back (v1);
		vertices.push_back (v2);
	}

	vertexNumber = vertices.size();
	vertexArray = new float[3*vertices.size()];

	for (unsigned int i=0; i<vertices.size(); ++i) {
		vertexArray[i*3] = vertices[i][0];
		vertexArray[i*3+1] = vertices[i][1];
		vertexArray[i*3+2] = -vertices[i][2];
	}
}

void GLGrid::setColor (const Vec3f& c) {
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
}

