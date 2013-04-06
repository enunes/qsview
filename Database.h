
#ifndef RELATIONS_H
#define RELATIONS_H

#include <vector>
#include <map>

#include "Segment.h"
#include "Net.h"
#include "Node.h"
#include "Terminal.h"

struct Database {

	MatrixCoord3D matrixSize;
	std::vector<Segment> segmentList;

	std::vector<Terminal> terminalList;

	std::vector<std::string> terminalLabels;

	std::vector<Net> netList;
	std::vector<std::string> netNames; // holds the names using the index

	std::map<std::string, unsigned int> namesMap; // maps a string name to its index for the other arrays;

	std::vector< std::vector<unsigned int> > netConnections;
	std::vector< std::vector<unsigned int> > segmentConnections;

	std::vector <unsigned int> unroutedList;
};


#endif
