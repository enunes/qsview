
#include "Vec3f.h"

Vec3f::Vec3f() {
	
}

Vec3f::Vec3f(float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

float &Vec3f::operator[](int index) {
	return v[index];
}

float Vec3f::operator[](int index) const {
	return v[index];
}

Vec3f Vec3f::operator*(float scale) const {
	return Vec3f(v[0] * scale, v[1] * scale, v[2] * scale);
}

Vec3f Vec3f::operator/(float scale) const {
	return Vec3f(v[0] / scale, v[1] / scale, v[2] / scale);
}

Vec3f Vec3f::operator+(const Vec3f &other) const {
	return Vec3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vec3f Vec3f::operator-(const Vec3f &other) const {
	return Vec3f(v[0] - other[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vec3f Vec3f::operator-() const {
	return Vec3f(-v[0], -v[1], -v[2]);
}

const Vec3f &Vec3f::operator*=(float scale) {
	v[0] *= scale;
	v[1] *= scale;
	v[2] *= scale;
	return *this;
}

const Vec3f &Vec3f::operator/=(float scale) {
	v[0] /= scale;
	v[1] /= scale;
	v[2] /= scale;
	return *this;
}

const Vec3f &Vec3f::operator+=(const Vec3f &other) {
	v[0] += other.v[0];
	v[1] += other.v[1];
	v[2] += other.v[2];
	return *this;
}

const Vec3f &Vec3f::operator-=(const Vec3f &other) {
	v[0] -= other.v[0];
	v[1] -= other.v[1];
	v[2] -= other.v[2];
	return *this;
}

float Vec3f::magnitude() const {
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float Vec3f::magnitudeSquared() const {
	return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

Vec3f Vec3f::normalize() const {
	float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return Vec3f(v[0] / m, v[1] / m, v[2] / m);
}

float Vec3f::dot(const Vec3f &other) const {
	return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}

Vec3f Vec3f::cross(const Vec3f &other) const {
	return Vec3f(v[1] * other.v[2] - v[2] * other.v[1],
				 v[2] * other.v[0] - v[0] * other.v[2],
				 v[0] * other.v[1] - v[1] * other.v[0]);
}

bool Vec3f::operator==(const Vec3f& other) const {
	return ((compareFloat(v[0], other.v[0], 0.01)) &&
			(compareFloat(v[1], other.v[1], 0.01)) &&
			(compareFloat(v[2], other.v[2], 0.01)));
}

Vec3f operator*(float scale, const Vec3f &v) {
	return v * scale;
}

std::ostream& operator<<(std::ostream& out, const Vec3f& v) {
	out << v[0] << " " << v[1] << " " << v[2];
	return out;
}

std::istream& operator>> (std::istream& in, Vec3f& v) {
	in >> v[0];
	in >> v[1];
	in >> v[2];
	return in;
}


void zeroThreshold (Vec3f& v, const float& threshold = 1e-6) {
	for (unsigned int i=0; i<3; ++i) {
		if (std::fabs(v[i]) < threshold) v[i] = 0.0f;
	}
}

