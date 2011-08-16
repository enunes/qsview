

#include "Node.h"

Node::Node () {
	s.clear();
	t = -1;
//	s[0] = s[1] = s[2] = t = -1;
}

std::ostream& operator<< (std::ostream& out, const Node& n) {
	std::cout << "(" << n.s << ") t=" << n.t;
	return out;
}
