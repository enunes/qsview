
#include "Segment.h"


Segment::Segment (const MatrixCoord3D& s, const unsigned int& a, const unsigned int& m, const unsigned int& n) {
	start = s;
	end = s;
	end[a] += m;

	axis = a;
	module = m;

	net = n;
}

std::ostream& operator<< (std::ostream& out, const Segment& s) {
	out << s.start << " " << s.end << " " << s.net;
	return out;
}
