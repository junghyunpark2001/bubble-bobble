#include "Player.h"
Player::Player(float x, float y, float s) : Texture() {
	pos[0] = x;
	pos[1] = y;
	size = s;
	state = ALIVE;
	vector<float> floor1 = { -290.0f, 290.0f };
	floors.push_back(make_pair(floor1, -290));
}
void Player::setPos(float x, float y) {
	pos[0] = x;
	pos[1] = y;
}
void Player::setVelocityX(float vx) {
	velocity[0] = vx;
}
void Player::setVelocityY(float vy) {
	velocity[1] = vy;
}
void Player::reset() {
	pos[0] = -290;
	pos[1] = 130;
	size = 20;
	state = ALIVE;
	setVerticalState(VERTICAL_STATE::FALL);
	setHorizontalState(HORIZONTAL_STATE::STOP);

	// Add additional reset steps as needed
}

void Player::setFace(FACE f) {
	face = f;
}
FACE Player::getFace() const {
	return face;
}
void Player::setHorizontalState(HORIZONTAL_STATE hState) {
	horizontalState = hState;
}
void Player::setVerticalState(VERTICAL_STATE vState) {
	verticalState = vState;
}
void Player::setfloors(vector<float> floorX, float floorY) {
	floors.push_back(make_pair(floorX, floorY));
}

bool Player::isDetectFloors() {
	Vec2 afterPos = pos + velocity;

	for (auto floor : floors) {
		if (afterPos[0] + PLAYER_WIDTH >= floor.first[0] && afterPos[0] <= floor.first[1]) {
			if (pos[1] >= floor.second && afterPos[1] <= floor.second ) {
				adj_floor = floor;
				//velocity[1] = pos[1] - floor.second;
				return true;
			}
		}
	}
	return false;
}


void Player::move() {
	switch (horizontalState) {
	case HORIZONTAL_STATE::STOP:
		velocity[0] = 0;
		break;
	case HORIZONTAL_STATE::MOVE:
		if (pos[0] + PLAYER_WIDTH <= RIGHT_WALL && pos[0] >= LEFT_WALL) {
			if (face == LEFT) {
				velocity[0] = -5.0f;
				if ((pos + velocity)[0] < LEFT_WALL) velocity[0] = LEFT_WALL - pos[0];
			}

			else if (face == RIGHT) {
				velocity[0] = 5.0f;
				if ((pos + velocity)[0] + PLAYER_WIDTH > RIGHT_WALL) velocity[0] = RIGHT_WALL - PLAYER_WIDTH - pos[0];
			}
		}
		if (pos[0] < LEFT_WALL) velocity[0] = 0;
		else if (pos[0] + PLAYER_WIDTH > RIGHT_WALL) velocity[0] = 0;
		break;
	}


	switch (verticalState) {
	case VERTICAL_STATE::STOP:
		velocity[1] = 0;
		if (!this->isDetectFloors()) {
			verticalState = VERTICAL_STATE::FALL;
		}
		break;
	case VERTICAL_STATE::JUMP:
		velocity[1] -= acceleration;
		if (this->isDetectFloors() && velocity[1] < 0) {
			verticalState = VERTICAL_STATE::STOP;
			velocity[1] = - pos[1] + adj_floor.second;
		}
		break;
	case VERTICAL_STATE::FALL:
		velocity[1] = -5.0f;
		if (this->isDetectFloors() && velocity[1] < 0) {
			verticalState = VERTICAL_STATE::STOP;
			velocity[1] = - pos[1] + adj_floor.second;
		}
		break;
	}

	pos += velocity;
	
}




void Player::draw() const {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, this->getTextureID());
	glBegin(GL_QUADS);

	if (face == RIGHT) {
		glTexCoord2f(0.0f, 0.0f);		glVertex2f(pos[0], pos[1]);
		glTexCoord2f(0.0f, 1.0f);		glVertex2f(pos[0], pos[1] + PLAYER_HEIGHT);
		glTexCoord2f(1.0f, 1.0f);		glVertex2f(pos[0] + PLAYER_WIDTH, pos[1] + PLAYER_HEIGHT);
		glTexCoord2f(1.0f, 0.0f);		glVertex2f(pos[0] + PLAYER_WIDTH, pos[1]);
	}
	else {
		glTexCoord2f(0.0f, 0.0f);		glVertex2f(pos[0] + PLAYER_WIDTH, pos[1]);
		glTexCoord2f(0.0f, 1.0f);		glVertex2f(pos[0] + PLAYER_WIDTH, pos[1] + PLAYER_HEIGHT);
		glTexCoord2f(1.0f, 1.0f);		glVertex2f(pos[0], pos[1] + PLAYER_HEIGHT);
		glTexCoord2f(1.0f, 0.0f);		glVertex2f(pos[0], pos[1]);
	}


	glEnd();

	// Disable texturing
	glDisable(GL_TEXTURE_2D);

}
Vec2 Player::getCenter() const {
	return Vec2(pos[0] + PLAYER_WIDTH / 2, pos[1] + PLAYER_HEIGHT / 2);
}

float Player::getCenterX() const {
	return pos[0] + PLAYER_WIDTH / 2;
}

float Player::getCenterY() const {
	return pos[1] + PLAYER_HEIGHT / 2;
}
float Player::getRadius() const {
	return 30;
}

void Player::setState(STATE st) {
	state = st;
}

bool Player::isAlive() const {
	return state == ALIVE;
}


void Player::createBubble() {
	bubbles.emplace_back(pos[0], pos[1], face); // Create a new bubble at the player's position
}

void Player::createBubbleDragon(float x, float y) {
	bubbles_dragon.push_back(Bubble(x - 30, y - 30));
}

Bubble::Bubble(float x, float y) : posX(x), posY(y) {
	state = FULL;
	size = 1.0f;
	velocityY = 5.0f;
	move = VERTICAL;
	center = Vec2(x + 30, y + 30);
}

Bubble::Bubble(float x, float y, float s) : posX(x), posY(y), face(s) {
	state = EMPTY;
	move = HORIZONTAL;
	center = Vec2(x + 30, y + 30);
}

void Bubble::drawBubble() const {


	glBegin(GL_QUADS);
	/*
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(posX+30-30*size, (posY + 50)-30*size);
	glTexCoord2f(0.0f, 1.0f);		glVertex2f(posX+30-30*size, (posY + 50)-30*size );
	glTexCoord2f(1.0f, 1.0f);		glVertex2f((posX + 30+30*size) , (posY + 50)-30*size );
	glTexCoord2f(1.0f, 0.0f);		glVertex2f((posX + 30+30*size) , (posY + 50)-30*size );
	*/

	/*
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(posX + 30 - 30 * size, (posY + 50) - 30 * size);
	glTexCoord2f(0.0f, 1.0f);		glVertex2f(posX + 30 - 30 * size, (posY + 50) + 30 * size);
	glTexCoord2f(1.0f, 1.0f);		glVertex2f((posX + 30 + 30 * size), (posY + 50) + 30 * size);
	glTexCoord2f(1.0f, 0.0f);		glVertex2f((posX + 30 + 30 * size), (posY + 50) - 30 * size);
	*/
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(center[0] - 30 * size, center[1] - 30 * size);
	glTexCoord2f(0.0f, 1.0f);		glVertex2f(center[0] - 30 * size, center[1] + 30 * size);
	glTexCoord2f(1.0f, 1.0f);		glVertex2f((center[0] + 30 * size), center[1] + 30 * size);
	glTexCoord2f(1.0f, 0.0f);		glVertex2f((center[0] + 30 * size), center[1] - 30 * size);
}

void Bubble::moveBubble() {
	if ((boundaryX - WALL_WIDTH) < center[0] + 30 * size || center[0] - 30 * size < (-boundaryX + WALL_WIDTH)) {
		size = 1.0f;
	}
	if (size < 1.0f) {

		size += 0.05f;
		if (face == RIGHT) {
			velocityX = 20.0f;
			center[0] += velocityX;
			size += 0.05f;
		}
		else if (face == LEFT) {
			velocityX = -20.0f;
			center[0] += velocityX;
			size += 0.05f;
		}

		if (center[0] + 30 * size + velocityX >= boundaryX - WALL_WIDTH) {
			size = 1.0f;
			velocityX = 0;
			center[0] = boundaryX - WALL_WIDTH - 30 * size;
		}
		else if (center[0] - 30 * size + velocityX <= -boundaryX + WALL_WIDTH) {
			size = 1.0f;
			velocityX = 0;
			center[0] = -boundaryX + WALL_WIDTH + 30 * size;
		}

	}
	else {
		move = VERTICAL;
		if (center[1] + 30 >= boundaryY - 30 - WALL_WIDTH - velocityY) {
			velocityY = 0;
			center[1] = 230;
		}
		center[1] += velocityY;
	}



}

float Bubble::getCenterX() const {
	return center[0];
}
float Bubble::getCenterY() const {
	return center[1];
}
Vec2 Bubble::getCenter() const {
	return center;
}
float Bubble::getRadius() const {
	return (30 * size);
}
float Bubble::getVelocityX() const {
	return velocityX;
}
float Bubble::getVelocityY() const {
	return velocityY;
}
void Bubble::setVelocityX(const float& x) {
	velocityX = x;
}
void Bubble::setVelocityY(const float& y) {
	velocityY = y;
}

void Bubble::setState(STATE st) {
	state = st;
}

bool Bubble::isEmpty() const {
	return state == EMPTY;
}

bool Bubble::isMoveVertical() const {
	return move == VERTICAL;
}

bool Bubble::operator==(const Bubble& bubble) const {
	if (this->getCenterX() == bubble.getCenterX() && this->getCenterY() == bubble.getCenterY()) {
		if (this->getVelocityX() == bubble.getVelocityX() && this->getVelocityY() == bubble.getVelocityY()) return true;
	}
	else return false;
}