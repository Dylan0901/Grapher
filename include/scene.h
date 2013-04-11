#ifndef SCENE_H
#define SCENE_H

#include "types3d.h"

class sector;

class Scene
{
private:
public:
    Sector sectors;
    Scene();
    ~Scene();
    void load(Sector&);
};

#endif // SCENE_H
