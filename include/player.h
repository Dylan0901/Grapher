#ifndef PLAYER_H
#define PLAYER_H

#include "events.h"
#include "types3d.h"

class Player
{
private:
    float x, y, z, angle_x, angle_y;
    float walkbias, walkbiasangle;
    bool keyUp, keyDown, keyLeft, keyRight, keyPageUp, keyPageDown;
public:
    Player();
    void move();
    void rotate(float, float);
    void onKeyEvent(EVENTS event);
    const Vertex getPosition();
    const Vertex getAngle();
};

#endif // PLAYER_H
