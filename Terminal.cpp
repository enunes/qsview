
#include "Terminal.h"

Terminal::Terminal() {
}

Terminal::Terminal (const MatrixCoord3D& newCoord, const unsigned int& newNet) :
	coord (newCoord), net (newNet) {
}

std::ostream& operator<< (std::ostream& out, const Terminal& theTerminal) {
	out << theTerminal.coord << " " << theTerminal.net;
	return out;
}

