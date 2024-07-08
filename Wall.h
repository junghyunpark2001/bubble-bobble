#pragma once
#include <iostream>
#include <GL/freeglut.h>
using namespace std;
class Wall
{
public:
	void setWidth(int w);
	int  getWidth() const;
	void draw_wall() const;
	void draw_polygon() const;
private:
	int width;
	int boundaryX = 320, boundaryY = 320;
	int WALL_WIDTH = 30;
};

