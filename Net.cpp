

#include "Net.h"

Net::Net () {
}

std::ostream& operator<< (std::ostream& out, const Net& n) {
	std::cout << n.terminals;
	return out;
}

