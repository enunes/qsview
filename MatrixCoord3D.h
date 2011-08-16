
#ifndef MATRIX_3D_COORD_H
#define MATRIX_3D_COORD_H

#include <cstdlib>
#include <iostream>

class MatrixCoord3D {
	public:
	int c[3];

	MatrixCoord3D ();
	MatrixCoord3D (const int& newX, const int& newY, const int& newZ);
	
	int& operator[] (const unsigned int& index);

	int operator[] (const unsigned int& index) const;

	MatrixCoord3D& operator+= (const MatrixCoord3D& otherCoord);
	MatrixCoord3D& operator-= (const MatrixCoord3D& otherCoord);
	MatrixCoord3D operator+ (const MatrixCoord3D& otherCoord) const;
	MatrixCoord3D operator- (const MatrixCoord3D& otherCoord) const;
	MatrixCoord3D operator- () const;

	void set (const int& newX, const int& newY, const int& newZ);
};


bool operator== (const MatrixCoord3D& coord1, const MatrixCoord3D& coord2);
bool operator!= (const MatrixCoord3D& coord1, const MatrixCoord3D& coord2);
std::ostream& operator<< (std::ostream& out, const MatrixCoord3D& theCoord);
std::istream& operator>> (std::istream& in, MatrixCoord3D& theCoord);
unsigned int distance (const MatrixCoord3D& coord1, const MatrixCoord3D& coord2);
MatrixCoord3D abs (const MatrixCoord3D& coord);
unsigned int module (const MatrixCoord3D& coord);
int direction (const MatrixCoord3D& coord1, const MatrixCoord3D& coord2);
unsigned int axis (const MatrixCoord3D& difference);
MatrixCoord3D orientation (const MatrixCoord3D& coord);

#endif

