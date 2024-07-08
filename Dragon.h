#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include "Vec2.h"
#include "Constants.h"
using namespace std;



class Dragon : public Vec2
{
public:
	enum class FACE_DRAGON { LEFT, RIGHT };
	enum STATE { ALIVE, BUBBLE, DEATH };

	Dragon();
	void move();
	void draw() const;
	Vec2 getCenter() const;
	float getCenterX() const;
	float getCenterY() const;
	float getRadius() const;
	void setVelocityX(const float& x);
	void setVelocityY(const float& y);
	void setPositionX(const float& x);
	void setPositionY(const float& y);

	void setState(STATE st);
	bool isAlive() const;
	bool isDead() const;

private:
	Vec2 pos;
	Vec2 velocity;
	float posX;
	float posY = -100;
	float speedX;
	float speedY;
	int directionX = 1;

	STATE state;


};

