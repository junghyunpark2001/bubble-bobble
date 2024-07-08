#pragma once
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "Texture.h"
#include "Constants.h"
#include "Vec2.h"
using namespace std;

enum FACE { LEFT, RIGHT };
enum class HORIZONTAL_STATE { STOP, MOVE };
enum class VERTICAL_STATE { STOP, JUMP, FALL };

class Bubble : public Vec2 {
public:
	enum STATE { EMPTY, FULL };
	enum MOVE { VERTICAL, HORIZONTAL };

	Bubble(float x, float y);
	Bubble(float x, float y, float s);

	void moveBubble();
	void drawBubble() const;

	float getCenterX() const;
	float getCenterY() const;
	Vec2 getCenter() const;
	float getRadius() const;
	float getVelocityX() const;
	float getVelocityY() const;
	void setVelocityX(const float& x);
	void setVelocityY(const float& y);

	void setState(STATE st);
	bool isEmpty() const;
	bool isMoveVertical() const;

	bool operator==(const Bubble& bubble) const;

private:
	Vec2 center;
	float posX;
	float posY;
	float radius;
	float face;
	float size = 0.1f;
	float velocityX;
	float velocityY;
	STATE state;
	MOVE move;

};



class Player : public Texture, public Vec2
{
public:
	enum STATE { ALIVE, DEATH };
	

	Player(float x, float y, float size);
	void setPos(float x, float y);
	void setVelocityX(float vx);
	void setVelocityY(float vy);
	void reset();
	
	void setFace(FACE f);
	FACE getFace() const;
	void setHorizontalState(HORIZONTAL_STATE hState);
	void setVerticalState(VERTICAL_STATE vState);
	void setfloors(vector<float> floorX, float floorY);
	//bool isDetectWall();
	bool isDetectFloors();
	void move();
	void draw() const;
	void createBubble();
	void createBubbleDragon(float x, float y);
	Vec2 getCenter() const;
	float getCenterX() const;
	float getCenterY() const;
	float getRadius() const;

	void setState(STATE st);
	bool isAlive() const;
	//void drawBubble() const;

	vector<Bubble> bubbles;
	vector<Bubble> bubbles_dragon;

private:
	float size;
	Vec2 pos;
	Vec2 velocity;
	float acceleration = 1.0f;
	
	vector<pair<vector<float>, float>> floors;
	pair<vector<float>, float> adj_floor;



	FACE face;
	HORIZONTAL_STATE horizontalState;
	VERTICAL_STATE verticalState;
	STATE state;
};