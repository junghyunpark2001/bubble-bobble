#pragma once
class Vec2
{
public:
	Vec2();
	Vec2(float x, float y);
	Vec2(const Vec2& v);
	void setPos(float x, float y);

	float& operator[](const int i);
	float operator[](const int i) const;

	Vec2& operator+=(Vec2& v);
	Vec2& operator-=(Vec2& v);
private:
	float pos[2];
};

Vec2 operator+(const Vec2& v1, const Vec2& v2);
Vec2 operator-(const Vec2& v1, const Vec2& v2);
//Vec2 operator*(Vec2& v, float s);
//Vec2 operator/(Vec2& v, float s);

float dotProduct(const Vec2& v1, const Vec2& v2);

