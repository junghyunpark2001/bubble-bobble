#include "Vec2.h"
Vec2::Vec2() {

}
Vec2::Vec2(float x, float y) {
	pos[0] = x;
	pos[1] = y;
}
Vec2::Vec2(const Vec2& v) {
	pos[0] = v.pos[0];
	pos[1] = v.pos[1];
}
void Vec2::setPos(float x, float y) {
	pos[0] = x;
	pos[1] = y;
}

float& Vec2::operator[](const int i) {
	return pos[i];
}
float Vec2::operator[](const int i) const {
	return pos[i];
}

Vec2& Vec2::operator+=(Vec2& v) {
	pos[0] += v.pos[0]; pos[1] += v.pos[1];
	return (*this);
}
Vec2& Vec2::operator-=(Vec2& v) {

	pos[0] -= v.pos[0]; pos[1] -= v.pos[1];
	return (*this);
}

Vec2 operator+(const Vec2& v1, const Vec2& v2) {
	return Vec2(v1[0] + v2[0], v1[1] + v2[1]);
}
Vec2 operator-(const Vec2& v1, const Vec2& v2) {
	return Vec2(v1[0] - v2[0], v1[1] - v2[1]);
}

float dotProduct(const Vec2& v1, const Vec2& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1];
}


