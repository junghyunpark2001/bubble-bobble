#include "Dragon.h"

Dragon::Dragon() {
    posX = 0;
    state = ALIVE;
}

void Dragon::move() {
    // Update the position based on speed and direction
    posX += speedX * directionX;
    posY += speedY;


    // Check boundaries and reverse direction if needed
    if (posX >= 120 || posX <= -120) {
        directionX *= -1;
    }


}



void Dragon::draw() const {
    glBegin(GL_QUADS);
    /*
    glTexCoord2f(0.0f, 0.0f);		glVertex2f(-30, 0);
    glTexCoord2f(0.0f, 1.0f);		glVertex2f(-30, 60);
    glTexCoord2f(1.0f, 1.0f);		glVertex2f(30, 60);
    glTexCoord2f(1.0f, 0.0f);		glVertex2f(30, 0);
    */
    if (directionX == -1) {
        glTexCoord2f(0.0f, 0.0f);		glVertex2f(posX - (DRAGON_WIDTH / 2), posY - (DRAGON_HEIGHT / 2));
        glTexCoord2f(0.0f, 1.0f);		glVertex2f(posX - (DRAGON_WIDTH / 2), posY + (DRAGON_HEIGHT / 2));
        glTexCoord2f(1.0f, 1.0f);		glVertex2f(posX + (DRAGON_WIDTH / 2), posY + (DRAGON_HEIGHT / 2));
        glTexCoord2f(1.0f, 0.0f);		glVertex2f(posX + (DRAGON_WIDTH / 2), posY - (DRAGON_HEIGHT / 2));
    }
    else {
        glTexCoord2f(0.0f, 0.0f);		glVertex2f(posX + (DRAGON_WIDTH / 2), posY - (DRAGON_HEIGHT / 2));
        glTexCoord2f(0.0f, 1.0f);		glVertex2f(posX + (DRAGON_WIDTH / 2), posY + (DRAGON_HEIGHT / 2));
        glTexCoord2f(1.0f, 1.0f);		glVertex2f(posX - (DRAGON_WIDTH / 2), posY + (DRAGON_HEIGHT / 2));
        glTexCoord2f(1.0f, 0.0f);		glVertex2f(posX - (DRAGON_WIDTH / 2), posY - (DRAGON_HEIGHT / 2));
    }
    glEnd();

    // Disable texturing
    glDisable(GL_TEXTURE_2D);

}
Vec2 Dragon::getCenter() const {
    return Vec2(posX, posY);
}

float Dragon::getCenterX() const {
    return posX;
}

float Dragon::getCenterY() const {
    return posY;
}
float Dragon::getRadius() const {
    return 30;
}
void Dragon::setVelocityX(const float& x) {
    speedX = x;
}
void Dragon::setVelocityY(const float& y) {
    speedY = y;
}
void Dragon::setPositionX(const float& x) {
    posX = x;
}
void Dragon::setPositionY(const float& y) {
    posY = y;
}
void Dragon::setState(STATE st) {
    state = st;
}
bool Dragon::isAlive() const {
    return state == ALIVE;
}
bool Dragon::isDead() const {
    return state == DEATH;
}