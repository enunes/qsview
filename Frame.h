
#ifndef FRAME_H
#define FRAME_H

#include "Vec3f.h"

class Frame {
	public:
	Vec3f position;
	Vec3f orientation;
	Vec3f up;

	Frame ();
	Frame (Vec3f newPosition, Vec3f newOrientation, Vec3f newUp);

	void moveFront (float factor = 1.0f);
	void moveBack (float factor = 1.0f);
	void moveRight (float factor = 1.0f);
	void moveLeft (float factor = 1.0f);
	void moveUp (float factor = 1.0f);
	void moveDown (float factor = 1.0f);

};

#endif

