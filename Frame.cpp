
#include "Frame.h"

Frame::Frame () {
	position = Vec3f (0.0f, 0.0f, 0.0f);
	orientation = Vec3f (1.0f, 0.0f, 0.0f);
	up = Vec3f (0.0f, 1.0f, 0.0f);
}

Frame::Frame (Vec3f newPosition, Vec3f newOrientation, Vec3f newUp) {
	position = newPosition;
	orientation = newOrientation;
	up = newUp;
}

void Frame::moveFront (float factor) {
	position += factor*orientation.normalize();
}

void Frame::moveBack (float factor) {
	position -= factor*orientation.normalize();
}
void Frame::moveRight (float factor) {
	Vec3f crossResult = orientation.cross(up).normalize();
	position += factor*(crossResult);
}
void Frame::moveLeft (float factor) {
	Vec3f crossResult = up.cross(orientation).normalize();
	position += factor*(crossResult);
}
void Frame::moveUp (float factor) {
	position += factor*up;
}
void Frame::moveDown (float factor) {
	position -= factor*up;
}
