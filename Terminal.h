
#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <iostream>
#include "MatrixCoord3D.h"

class Terminal {
	public:
	MatrixCoord3D coord;
	unsigned int net;

	Terminal ();
	Terminal (const MatrixCoord3D& newCoord, const unsigned int& newNet);
};

std::ostream& operator<< (std::ostream& out, const Terminal& theTerminal);

#endif

