
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include "utils.h"

class Node {
	public:
	int t;
	std::vector<unsigned int> s;

	Node ();
};

std::ostream& operator<< (std::ostream& out, const Node& n);

#endif

