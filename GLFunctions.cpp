
#include "GLFunctions.h"

void buildSegmentVertices (const Segment& s, const Vec3f& color, const float& pitch, const float& height, const float& thickness, const unsigned int& offset, float* vertexArray, float* colorArray, unsigned int *ind) {

	const MatrixCoord3D& start = s.start;
	const MatrixCoord3D& end = s.end;

	Vec3f xyz (static_cast<float>(start[0])*pitch, static_cast<float>(start[2])*height, static_cast<float>(start[1])*pitch);
	Vec3f XYZ (static_cast<float>(end[0])*pitch, static_cast<float>(end[2])*height, static_cast<float>(end[1])*pitch);

	const float buffer = -xyz[2];
	xyz[2] = -XYZ[2];
	XYZ[2] = buffer;

	xyz -= Vec3f (thickness, thickness, thickness); // 0
	XYZ += Vec3f (thickness, thickness, thickness); // 1


	Vec3f Xyz = xyz; // 2
	Xyz[0] = XYZ[0];

	Vec3f xYz = xyz; // 3
	xYz[1] = XYZ[1];

	Vec3f xyZ = xyz; // 4
	xyZ[2] = XYZ[2];
 
	Vec3f XYz = XYZ; // 5
	XYz[2] = xyz[2];

	Vec3f XyZ = XYZ; // 6
	XyZ[1] = xyz[1];

	Vec3f xYZ = XYZ; // 7
	xYZ[0] = xyz[0];

	std::vector<Vec3f> vertices;
	vertices.push_back (xyz);
	vertices.push_back (XYZ);
	vertices.push_back (Xyz);
	vertices.push_back (xYz);
	vertices.push_back (xyZ);
	vertices.push_back (XYz);
	vertices.push_back (XyZ);
	vertices.push_back (xYZ);

	for (unsigned int i=0; i<8; ++i) {
		vertexArray[i*3] = vertices[i][0];
		vertexArray[i*3+1] = vertices[i][1];
		vertexArray[i*3+2] = vertices[i][2];

		colorArray[i*3] = color[0];
		colorArray[i*3+1] = color[1];
		colorArray[i*3+2] = color[2];
	}


	ind[ 0] = offset + 0;
	ind[ 1] = offset + 2;
	ind[ 2] = offset + 5;
	ind[ 3] = offset + 0;
	ind[ 4] = offset + 5;
	ind[ 5] = offset + 3;

	ind[ 6] = offset + 4;
	ind[ 7] = offset + 6;
	ind[ 8] = offset + 1;
	ind[ 9] = offset + 4;
	ind[10] = offset + 1;
	ind[11] = offset + 7;

	ind[12] = offset + 0;
	ind[13] = offset + 4;
	ind[14] = offset + 6;
	ind[15] = offset + 0;
	ind[16] = offset + 6;
	ind[17] = offset + 2;

	ind[18] = offset + 3;
	ind[19] = offset + 7;
	ind[20] = offset + 1;
	ind[21] = offset + 3;
	ind[22] = offset + 1;
	ind[23] = offset + 5;

	ind[24] = offset + 0;
	ind[25] = offset + 4;
	ind[26] = offset + 7;
	ind[27] = offset + 0;
	ind[28] = offset + 7;
	ind[29] = offset + 3;

	ind[30] = offset + 2;
	ind[31] = offset + 6;
	ind[32] = offset + 1;
	ind[33] = offset + 2;
	ind[34] = offset + 1;
	ind[35] = offset + 5;
}

	//vertices.push_back (xyz); // 0
	//vertices.push_back (Xyz); // 2
	//vertices.push_back (XYz); // 5
	//vertices.push_back (xyz); // 0 
	//vertices.push_back (XYz); // 5
	//vertices.push_back (xYz); // 3
	//vertices.push_back (xyZ); // 4
	//vertices.push_back (XyZ); // 6
	//vertices.push_back (XYZ); // 1
	//vertices.push_back (xyZ); // 4
	//vertices.push_back (XYZ); // 1
	//vertices.push_back (xYZ); // 7
	//vertices.push_back (xyz); // 0
	//vertices.push_back (xyZ); // 4
	//vertices.push_back (XyZ); // 6
	//vertices.push_back (xyz); // 0
	//vertices.push_back (XyZ); // 6
	//vertices.push_back (Xyz); // 2
	//vertices.push_back (xYz); // 3
	//vertices.push_back (xYZ); // 7
	//vertices.push_back (XYZ); // 1
	//vertices.push_back (xYz); // 3
	//vertices.push_back (XYZ); // 1
	//vertices.push_back (XYz); // 5
	//vertices.push_back (xyz); // 0
	//vertices.push_back (xyZ); // 4
	//vertices.push_back (xYZ); // 7
	//vertices.push_back (xyz); // 0
	//vertices.push_back (xYZ); // 7
	//vertices.push_back (xYz); // 3
	//vertices.push_back (Xyz); // 2
	//vertices.push_back (XyZ); // 6
	//vertices.push_back (XYZ); // 1
	//vertices.push_back (Xyz); // 2
	//vertices.push_back (XYZ); // 1
	//vertices.push_back (XYz); // 5


void buildTerminalVertices (const MatrixCoord3D& c, const Vec3f& color, const float& pitch, const float& height, const float& thickness, const unsigned int& offset, float* vertexArray, float* colorArray, unsigned int *ind) {

	Vec3f xyz (static_cast<float>(c[0])*pitch, static_cast<float>(c[2])*height, static_cast<float>(c[1])*pitch);
	Vec3f XYZ = xyz;

	const float buffer = -xyz[2];
	xyz[2] = -XYZ[2];
	XYZ[2] = buffer;

	xyz -= Vec3f (thickness, thickness, thickness); // 0
	XYZ += Vec3f (thickness, thickness, thickness); // 1

	Vec3f Xyz = xyz; // 2
	Xyz[0] = XYZ[0];

	Vec3f xYz = xyz; // 3
	xYz[1] = XYZ[1];

	Vec3f xyZ = xyz; // 4
	xyZ[2] = XYZ[2];
 
	Vec3f XYz = XYZ; // 5
	XYz[2] = xyz[2];

	Vec3f XyZ = XYZ; // 6
	XyZ[1] = xyz[1];

	Vec3f xYZ = XYZ; // 7
	xYZ[0] = xyz[0];


	std::vector<Vec3f> vertices;
	vertices.push_back (xyz);
	vertices.push_back (XYZ);
	vertices.push_back (Xyz);
	vertices.push_back (xYz);
	vertices.push_back (xyZ);
	vertices.push_back (XYz);
	vertices.push_back (XyZ);
	vertices.push_back (xYZ);


	for (unsigned int i=0; i<8; ++i) {
		vertexArray[i*3] = vertices[i][0];
		vertexArray[i*3+1] = vertices[i][1];
		vertexArray[i*3+2] = vertices[i][2];

		colorArray[i*3] = color[0];
		colorArray[i*3+1] = color[1];
		colorArray[i*3+2] = color[2];
	}


	ind[ 0] = offset + 0;
	ind[ 1] = offset + 2;
	ind[ 2] = offset + 5;
	ind[ 3] = offset + 0;
	ind[ 4] = offset + 5;
	ind[ 5] = offset + 3;

	ind[ 6] = offset + 4;
	ind[ 7] = offset + 6;
	ind[ 8] = offset + 1;
	ind[ 9] = offset + 4;
	ind[10] = offset + 1;
	ind[11] = offset + 7;

	ind[12] = offset + 0;
	ind[13] = offset + 4;
	ind[14] = offset + 6;
	ind[15] = offset + 0;
	ind[16] = offset + 6;
	ind[17] = offset + 2;

	ind[18] = offset + 3;
	ind[19] = offset + 7;
	ind[20] = offset + 1;
	ind[21] = offset + 3;
	ind[22] = offset + 1;
	ind[23] = offset + 5;

	ind[24] = offset + 0;
	ind[25] = offset + 4;
	ind[26] = offset + 7;
	ind[27] = offset + 0;
	ind[28] = offset + 7;
	ind[29] = offset + 3;

	ind[30] = offset + 2;
	ind[31] = offset + 6;
	ind[32] = offset + 1;
	ind[33] = offset + 2;
	ind[34] = offset + 1;
	ind[35] = offset + 5;
}


AABB buildBox (const Segment& s, const float& pitch, const float& height, const float& thickness) {
	const MatrixCoord3D& start = s.start;
	const MatrixCoord3D& end = s.end;

	Vec3f xyz (static_cast<float>(start[0])*pitch, static_cast<float>(start[2])*height, static_cast<float>(start[1])*pitch);
	Vec3f XYZ (static_cast<float>(end[0])*pitch, static_cast<float>(end[2])*height, static_cast<float>(end[1])*pitch);

	// must swap z and Z. because -XYZ will yield the smallest negative value for Z, that needs to be swapped so that the xyz and XYZ points get right for AABB creation.
	const float buffer = -xyz[2];
	xyz[2] = -XYZ[2];
	XYZ[2] = buffer;

	xyz -= Vec3f (thickness, thickness, thickness); // 0
	XYZ += Vec3f (thickness, thickness, thickness); // 1

	return AABB (xyz, XYZ);
}

AABB buildBox (const MatrixCoord3D& c, const float& pitch, const float& height, const float& thickness) {
	Vec3f xyz (static_cast<float>(c[0])*pitch, static_cast<float>(c[2])*height, static_cast<float>(c[1])*pitch);
	Vec3f XYZ = xyz;

	// this works. because -XYZ will yield the smallest negative value for Z. that needs to be swapped so that the xyz and XYZ points get right for AABB creation.
	const float buffer = -xyz[2];
	xyz[2] = -XYZ[2];
	XYZ[2] = buffer;

	xyz -= Vec3f (thickness, thickness, thickness); // 0
	XYZ += Vec3f (thickness, thickness, thickness); // 1

	return AABB (xyz, XYZ);
}

