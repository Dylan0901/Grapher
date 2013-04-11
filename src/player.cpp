#define PI_OVER_180 0.0174532925f

#include "player.h"
#include <cmath>

Player::Player()
{
    keyUp = keyDown = keyLeft = keyRight = keyPageUp = keyPageDown = false;
    x = -9;
    y = 0;
    z = -9;
    angle_x = angle_y = 0;
    walkbias = walkbiasangle = 0.0f;
}

void Player::move() {
    if (keyUp) {
        x += sin(angle_x * PI_OVER_180) * 0.15f;
        z += cos(angle_x * PI_OVER_180) * 0.15f;
        if (walkbiasangle >= 353.0f)
            walkbiasangle = 0.0f;
        else
            walkbiasangle += 7.0f;
        walkbias = sin(walkbiasangle * PI_OVER_180) / 20.0f;
        y = walkbias;
    } else if (keyDown) {
        x -= sin(angle_x * PI_OVER_180) * 0.15f;
        z -= cos(angle_x * PI_OVER_180) * 0.15f;
        if (walkbiasangle <= 7.0f)
            walkbiasangle = 353.0f;
        else
            walkbiasangle -= 7.0f;
        walkbias = sin(walkbiasangle * PI_OVER_180) / 20.0f;
        y = walkbias;
    }

    if (keyLeft) {
        x += cos(angle_x * PI_OVER_180) * 0.15f;
        z -= sin(angle_x * PI_OVER_180) * 0.15f;
    } else if (keyRight) {
        x -= cos(angle_x * PI_OVER_180) * 0.15f;
        z += sin(angle_x * PI_OVER_180) * 0.15f;
    }
}

void Player::rotate(float rx, float ry) {
    angle_x -= rx/ 10.0f;
    angle_y += ry/ 10.0f;
    if (angle_x > 360) {
        angle_x = (int)angle_x % 360;
    }
    if (angle_x < -360) {
        angle_x = (int)angle_x % 360;
    }
    if (angle_y > 90.0f) {
        angle_y = 90.0f;
    }
    if (angle_y < -90.0f) {
        angle_y = -90.0f;
    }
}

const Vertex Player::getPosition() {
    return Vertex(x, y, z);
}

const Vertex Player::getAngle() {
    return Vertex(angle_x, angle_y, 0);
}

void Player::onKeyEvent(EVENTS event) {
    switch(event) {
    case up_key_pressed:
        keyUp = true;
        break;
    case down_key_pressed:
        keyDown = true;
        break;
    case left_key_pressed:
        keyLeft = true;
        break;
    case right_key_pressed:
        keyRight = true;
        break;
    case up_key_released:
        keyUp = false;
        break;
    case down_key_released:
        keyDown = false;
        break;
    case left_key_released:
        keyLeft = false;
        break;
    case right_key_released:
        keyRight = false;
        break;
    }
}
