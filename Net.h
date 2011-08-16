
#ifndef NET_H
#define NET_H

#include <iostream>
#include <vector>
#include "MatrixCoord3D.h"
#include "utils.h"

class Net {
	public:
	std::vector<unsigned int> terminals;

	Net ();
};

std::ostream& operator<< (std::ostream& out, const Net& n);

#endif

