
#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cmath>
#include <vector>
#include <list>
#include <set>
#include <ostream>

float degToRad (int deg);
bool compareFloat (float f1, float f2, float error);

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& theVector) {
	for (unsigned int i=0; i<theVector.size(); i++) {
		out << theVector[i] << " ";
	}
	return out;
}


template <typename T>
std::ostream& operator<< (std::ostream& out, const std::list<T>& theList) {
	for (typename std::list<T>::const_iterator it = theList.begin(); it != theList.end(); ++it) {
		const T& i = *it;
		out << i << " ";
	}
	return out;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::set<T>& theSet) {
	for (typename std::set<T>::const_iterator it = theSet.begin(); it != theSet.end(); ++it) {
		const T& i = *it;
		out << i << " ";
	}
	return out;
}


#endif

