

#include "MatrixCoord3D.h"

MatrixCoord3D::MatrixCoord3D () {
	c[0] = c[1] = c[2] = 0;
}

MatrixCoord3D::MatrixCoord3D (const int& newX, const int& newY, const int& newZ) {
	c[0] = newX;
	c[1] = newY;
	c[2] = newZ;
}

MatrixCoord3D& MatrixCoord3D::operator+= (const MatrixCoord3D& otherCoord) {
	c[0] += otherCoord.c[0];
	c[1] += otherCoord.c[1];
	c[2] += otherCoord.c[2];
	return *this;
}

MatrixCoord3D& MatrixCoord3D::operator-= (const MatrixCoord3D& otherCoord) {
	c[0] -= otherCoord.c[0];
	c[1] -= otherCoord.c[1];
	c[2] -= otherCoord.c[2];
	return *this;
}

MatrixCoord3D MatrixCoord3D::operator+ (const MatrixCoord3D& otherCoord) const {
	return MatrixCoord3D (c[0]+otherCoord.c[0],
		       	c[1]+otherCoord.c[1],
			c[2]+otherCoord.c[2]);
}

MatrixCoord3D MatrixCoord3D::operator- (const MatrixCoord3D& otherCoord) const {
	return MatrixCoord3D (c[0]-otherCoord.c[0],
		       	c[1]-otherCoord.c[1],
		       	c[2]-otherCoord.c[2]);
}
MatrixCoord3D MatrixCoord3D::operator- () const {
	return MatrixCoord3D (-c[0], -c[1], -c[2]);
}

bool operator== (const MatrixCoord3D& coord1, const MatrixCoord3D& coord2) {
	return ((coord1.c[0] == coord2.c[0]) &&
		(coord1.c[1] == coord2.c[1]) &&
		(coord1.c[2] == coord2.c[2]));

}

bool operator!= (const MatrixCoord3D& coord1, const MatrixCoord3D& coord2) {
	return (!(coord1 == coord2));
}

std::ostream& operator<< (std::ostream& out, const MatrixCoord3D& theCoord) {
	out << theCoord.c[0] << " " << theCoord.c[1] << " " << theCoord.c[2];
	return out;
}

std::istream& operator>> (std::istream& in, MatrixCoord3D& theCoord) {
	in >> theCoord.c[0];
	in >> theCoord.c[1];
	in >> theCoord.c[2];
	return in;
}

void MatrixCoord3D::set (const int& newX, const int& newY, const int& newZ) {
	c[0] = newX;
	c[1] = newY;
	c[2] = newZ;
}

unsigned int distance (const MatrixCoord3D& coord1, const MatrixCoord3D& coord2) {
	return std::abs(coord1.c[0]-coord2.c[0]) + std::abs(coord1.c[1]-coord2.c[1]) + std::abs(coord1.c[2]-coord2.c[2]);
}

MatrixCoord3D abs (const MatrixCoord3D& coord) {
	return MatrixCoord3D (std::abs(coord.c[0]), std::abs(coord.c[1]), std::abs(coord.c[2]));
}

unsigned int module (const MatrixCoord3D& coord) {
	return std::abs(coord.c[0]) + std::abs(coord.c[1]) + std::abs(coord.c[2]);
}

int direction (const MatrixCoord3D& coord1, const MatrixCoord3D& coord2) {
	// To be used with responsibility. Do not pass coords that differ in two axis.
	const MatrixCoord3D difference = coord2 - coord1;
	if (difference.c[0] != 0) return 0;
	else if (difference.c[1] != 0) return 1;
	else if (difference.c[2] != 0) return 2;
	else return -1;
}

unsigned int axis (const MatrixCoord3D& difference) {
	if (difference[0] != 0) return 0;
	if (difference[1] != 0) return 1;
	return 2;
}

MatrixCoord3D orientation (const MatrixCoord3D& coord) {
	if (coord[0] < 0) return MatrixCoord3D (-1, 0, 0);
	else if (coord[0] > 0) return MatrixCoord3D (1, 0, 0);
	else if (coord[1] < 0) return MatrixCoord3D (0, -1, 0);
	else if (coord[1] > 0) return MatrixCoord3D (0, 1, 0);
	else if (coord[2] < 0) return MatrixCoord3D (0, 0, -1);
	else return MatrixCoord3D (0, 0, 1);
}

int& MatrixCoord3D::operator[] (const unsigned int& index) {
	return c[index];
}

int MatrixCoord3D::operator[] (const unsigned int& index) const {
	return c[index];
}


