
#include "GLSegment.h"

GLSegment::GLSegment () {
}

std::ostream& operator<< (std::ostream& out, const GLSegment& gls) {
	out << gls.ind;
	return out;
}
