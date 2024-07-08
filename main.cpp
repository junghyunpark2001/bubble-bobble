#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include <GL/FreeImage.h>

#include "Texture.h"
#include "Wall.h"
#include "Player.h"
#include "Dragon.h"
#include "Vec2.h"

#include <Windows.h>


#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

//float pos[2];
//bool bPressLeft, bPressRight;

clock_t start_t = clock();
clock_t end_t;

Texture texture;
Wall wall;
Player player(0, 0, 20);
Texture dragon;
Dragon dragon_position;
Texture bubble;
Texture bubble_dragon;


void playSound() {
	PlaySound(TEXT("bubbobble.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
}
void initialize() {
	texture.initializeTexture("snu.png");
	dragon.initializeTexture("dragon.png");
	player.initializeTexture("Bubblun.png");
	bubble.initializeTexture("bubble.png");
	bubble_dragon.initializeTexture("bubble_dragon.png");
	playSound();
	player.setPos(-290, 130);

	player.setfloors({ -290, -210 }, -130);
	player.setfloors({ -130, 130 }, -130);
	player.setfloors({ 210, 290 }, -130);

	player.setfloors({ -290, -210 }, 30);
	player.setfloors({ -130, 130 }, 30);
	player.setfloors({ 210, 290 }, 30);

	if (player.isDetectFloors()) player.setVerticalState(VERTICAL_STATE::STOP);
	else player.setVerticalState(VERTICAL_STATE::FALL);
	
	dragon_position.setVelocityX(3.0f);
	dragon_position.setVelocityY(0.0f);
}

void displayCharacters(void* font, string str, float x, float y) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	for (int i = 0; i < (int)str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}

void drawSquareWithTexture() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
	wall.draw_wall();
	glDisable(GL_TEXTURE_2D);
}

void drawDragonWithTexture() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, dragon.getTextureID());
	dragon_position.draw();
	glDisable(GL_TEXTURE_2D);
}

void drawBubbleWithTexture() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, bubble.getTextureID());
	for (const auto& bubble : player.bubbles) {
		bubble.drawBubble();
	}


	glEnd();


	glDisable(GL_TEXTURE_2D);
}

void drawBubbleDragonWithTextrue() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, bubble_dragon.getTextureID());
	for (const auto& bubble_dragon : player.bubbles_dragon) {
		bubble_dragon.drawBubble();
	}


	glEnd();

	glDisable(GL_TEXTURE_2D);
}
//Collision between player and dragon
bool isCollisionDetected(const Player& player, const Dragon& dragon) {
	Vec2 diff = player.getCenter() - dragon.getCenter();

	if (player.isAlive() && dragon.isAlive()) {
		if (diff[0] < (PLAYER_WIDTH + DRAGON_WIDTH) / 2 && diff[0] > -(PLAYER_WIDTH + DRAGON_WIDTH) / 2) {
			if (diff[1] < (PLAYER_HEIGHT + DRAGON_HEIGHT) / 2 && diff[1] > -(PLAYER_HEIGHT + DRAGON_HEIGHT) / 2) {
				return true;
			}
		}
	}

	return false;
}

void handleCollision(Player& player, Dragon& dragon) {
	if (isCollisionDetected(player, dragon)) {
		player.setState(Player::STATE::DEATH);
	}
}
// Collision between dragon and bubble
bool isCollisionDetected(const Dragon& dragon, const Bubble& bubble) {
	if (dragon.isAlive() && player.isAlive()) {		
		float dx = dragon.getCenterX() - bubble.getCenterX();
		float dy = dragon.getCenterY() - bubble.getCenterY();

		float distance = sqrtf(dx * dx + dy * dy);

		//return dragon.getRadius() + bubble.getRadius() > distance;
		if (!bubble.isMoveVertical() && bubble.isEmpty()) return 20 > distance;
		else return false;
		
		
	}
	else return false;
	
}

void handleCollision(Dragon& dragon, Bubble& bubble) {
	if (isCollisionDetected(dragon, bubble)) {
		dragon.setState(Dragon::STATE::BUBBLE);
		bubble.setState(Bubble::STATE::FULL);

		player.createBubbleDragon(bubble.getCenter()[0], bubble.getCenter()[1]); // Create a bubble_dragon when a collision between dragon and bubble is detected
		player.bubbles.erase(remove(player.bubbles.begin(), player.bubbles.end(), bubble), player.bubbles.end());

		
		//dragon.setPositionX(bubble.getCenterX());
		//dragon.setPositionY(bubble.getCenterY());
		//dragon.setVelocityX(bubble.getVelocityX());
		dragon.setVelocityX(0.0f);
		dragon.setVelocityY(5.0f);
		//dragon.setVelocityY(bubble.getVelocityY());

	}
	else {
		bubble.setVelocityY(5.0f);
	}
}
// Collision between player and bubble
bool isCollisionDetected(const Player& player, const Bubble& bubble) {
	if (player.isAlive() && bubble.isMoveVertical()) {
		Vec2 d = player.getCenter() - bubble.getCenter();

		float distance = sqrtf(d[0] * d[0] + d[1] * d[1]);

		//return dragon.getRadius() + bubble.getRadius() > distance;
		return player.getRadius() + bubble.getRadius() > distance;
	}
	else return false;

}

void handleCollision(Player& player, Bubble& bubble) {
	if (isCollisionDetected(player, bubble)) {

		player.bubbles.erase(remove(player.bubbles.begin(), player.bubbles.end(), bubble), player.bubbles.end());
		//player.createBubbleDragon(bubble.getCenter()[0], bubble.getCenter()[1]); // Create a bubble_dragon when a collision between dragon and bubble is detected
		player.bubbles_dragon.erase(remove(player.bubbles_dragon.begin(), player.bubbles_dragon.end(), bubble), player.bubbles_dragon.end());
		if (!bubble.isEmpty()) dragon_position.setState(Dragon::STATE::DEATH);

	}
}

void idle() {
	end_t = clock();
	bool collide = 0;
	if ((float)(end_t - start_t) > 1000 / 30.0f) {
		
		for (auto& bubble : player.bubbles) {
			handleCollision(dragon_position, bubble);
			handleCollision(player, bubble);
		}

		for (auto& bubble : player.bubbles_dragon) {
			handleCollision(player, bubble);
		}
		dragon_position.move();

		handleCollision(player, dragon_position);
		player.move();

		for (auto& bubble : player.bubbles) bubble.moveBubble();
		
		for (auto& bubbledragon : player.bubbles_dragon) bubbledragon.moveBubble();

		start_t = end_t;
		glutPostRedisplay();
	}
}

void specialKeyDown(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		
		player.setFace(LEFT);
		player.setHorizontalState(HORIZONTAL_STATE::MOVE);
		break;
	case GLUT_KEY_RIGHT:
		
		player.setFace(RIGHT);
		player.setHorizontalState(HORIZONTAL_STATE::MOVE);
		break;
	case GLUT_KEY_UP:
		if (player.isDetectFloors()) {
			player.setVelocityY(18.6f);
			player.setVerticalState(VERTICAL_STATE::JUMP);
		}

		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void specialKeyUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		player.setHorizontalState(HORIZONTAL_STATE::STOP);
		
		break;
	case GLUT_KEY_RIGHT:
		player.setHorizontalState(HORIZONTAL_STATE::STOP);
		
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y) {
	/*
	if (key == ' ') { // Check for Enter key (ASCII code 13)
		player.createBubble(); // Create a bubble when Enter is pressed
	}
	else if (key == 'r' && !player.isAlive()) {

		player.reset();
	}
	else if (key == 'e' && !player.isAlive()) {
		// Terminate the program when 'e' is pressed after a collision
		exit(0);
	}
	*/
	switch (key) {
	case ' ':
		player.createBubble();
		break;
	case 'r':
		if (!player.isAlive()) {
			player.reset();
			player.bubbles.clear();
		}	
		break;
	case 'e':
		if (!player.isAlive() || dragon_position.isDead()) exit(0);
		break;
	default:
		break;
	}



}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);
	//gluOrtho2D(-boundaryX, boundaryX, -boundaryY, boundaryY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw 2D
	drawSquareWithTexture();
	wall.draw_polygon();

	if (dragon_position.isAlive()) drawDragonWithTexture(); // dragon 개수 증가시키면 바꿔주어야 함.
	

	player.draw();
	drawBubbleWithTexture();
	drawBubbleDragonWithTextrue();

	if (!player.isAlive()) {
		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER", -boundaryX * 0.25f, boundaryY * 0.4f);

		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "E : EXIT GAME", -boundaryX * 0.4f, boundaryY * -0.63f);
		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "R : RESTART GAME", -boundaryX * 0.4f, boundaryY * -0.83f);
	}

	if (dragon_position.isDead()) {
		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "CONGRATULATION!!", -boundaryX * 0.4f, boundaryY * 0.4f);

		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "E : EXIT GAME", -boundaryX * 0.4f, boundaryY * -0.73f);
		//displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "R : RESTART GAME", -boundaryX * 0.4f, boundaryY * -0.83f);
	}

	// Draw 3D
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("BubbleBobble");

	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	glutKeyboardFunc(keyPressed);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}