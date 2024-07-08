#include "Wall.h"

void Wall::setWidth(int w) {
	width = w;
}

int Wall::getWidth() const {
	return width;
}

void Wall::draw_wall() const {
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-boundaryX, -boundaryY);
	glTexCoord2f(0.0f, 1.0f);		glVertex2f(-boundaryX, boundaryY - 30);
	glTexCoord2f(1.0f, 1.0f);		glVertex2f(boundaryX, boundaryY - 30);
	glTexCoord2f(1.0f, 0.0f);		glVertex2f(boundaryX, -boundaryY);
	glEnd();
}

void Wall::draw_polygon() const {
	glColor3f(0.0f, 0.0f, 0.0f);
	
	for (int i = 0; i < 2; i++) {
		glBegin(GL_POLYGON);
		glVertex2f(-boundaryX + WALL_WIDTH, -boundaryY + WALL_WIDTH + 160*i); // A 
		glVertex2f(-boundaryX + WALL_WIDTH, -boundaryY + WALL_WIDTH + 130 + 160*i); // B 
		glVertex2f(boundaryX - WALL_WIDTH, -boundaryY + WALL_WIDTH + 130 + 160*i); // C 
		glVertex2f(boundaryX - WALL_WIDTH, -boundaryY + WALL_WIDTH + 160*i); // D 
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(-boundaryX + WALL_WIDTH + 80, -boundaryY + WALL_WIDTH + 130 + 160 * i); // A 
		glVertex2f(-boundaryX + WALL_WIDTH + 80, -boundaryY + WALL_WIDTH + 160 + 160 * i); // B 
		glVertex2f(-130, -boundaryY + WALL_WIDTH + 160 + 160 * i); // C 
		glVertex2f(-130, -boundaryY + WALL_WIDTH + 130 + 160 * i); // D 
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(130, -boundaryY + WALL_WIDTH + 130 + 160 * i); // A 
		glVertex2f(130, -boundaryY + WALL_WIDTH + 160 + 160 * i); // B 
		glVertex2f(boundaryX - WALL_WIDTH - 80, -boundaryY + WALL_WIDTH + 160 + 160 * i); // C 
		glVertex2f(boundaryX - WALL_WIDTH - 80, -boundaryY + WALL_WIDTH + 130 + 160 * i); // D 
		glEnd();
	}

	glBegin(GL_POLYGON);
	glVertex2f(-boundaryX + WALL_WIDTH, boundaryY - WALL_WIDTH - 260); // A 
	glVertex2f(-boundaryX + WALL_WIDTH, boundaryY - WALL_WIDTH - 30); // B 
	glVertex2f(boundaryX - WALL_WIDTH, boundaryY - WALL_WIDTH - 30); // C 
	glVertex2f(boundaryX - WALL_WIDTH, boundaryY - WALL_WIDTH - 260); // D 
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-boundaryX + WALL_WIDTH + 80, boundaryY - WALL_WIDTH - 290); // A 
	glVertex2f(-boundaryX + WALL_WIDTH + 80, boundaryY - WALL_WIDTH - 260); // B 
	glVertex2f(-130, boundaryY - WALL_WIDTH - 260); // C 
	glVertex2f(-130, boundaryY - WALL_WIDTH - 290); // D 
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(130, boundaryY - WALL_WIDTH - 290); // A 
	glVertex2f(130, boundaryY - WALL_WIDTH - 260); // B 
	glVertex2f(boundaryX - WALL_WIDTH - 80, boundaryY - WALL_WIDTH - 260); // C 
	glVertex2f(boundaryX - WALL_WIDTH - 80, boundaryY - WALL_WIDTH - 290); // D 
	glEnd();
}