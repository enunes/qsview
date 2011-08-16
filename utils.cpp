
#include "utils.h"

float degToRad (int deg) {
	return ((float)((2.0*M_PI*deg)/360.0));
}

bool compareFloat (float f1, float f2, float error) {
	if (fabs(f2 - f1) < error) return true;
	return false;
}

