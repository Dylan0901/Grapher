#ifndef MODEL_H
#define MODEL_H

#include "events.h"
#include "types3d.h"
#include <QObject>

class Player;
class Scene;

class Model
{
private:
    Scene* scene;
    Player* player;
    Bundle bundle;
public:
    Model();
    ~Model();
    void play();
    void rotate(float, float);
    Bundle& getBundle();
    void omitEvent(EVENTS);
};

#endif // MODEL_H
