
#ifndef SEGMENT_H
#define SEGMENT_H

#include <iostream>
#include "Vec3f.h"
#include "MatrixCoord3D.h"

class Segment {
	public:
	MatrixCoord3D start;
	MatrixCoord3D end;
	unsigned int axis;
	unsigned int module;
	
	unsigned int net;

	Segment (const MatrixCoord3D& s, const unsigned int& a, const unsigned int& m, const unsigned int& n);
};

std::ostream& operator<< (std::ostream& out, const Segment& s);

#endif
