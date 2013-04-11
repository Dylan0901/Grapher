#include "model.h"
#include "objloader.h"
#include "types3d.h"
#include "player.h"
#include "scene.h"

Model::Model()
{
    ObjLoader loader;
    scene = new Scene;
    Sector sector = loader.load("world.obj");
    scene->load(sector);
    player = new Player;
}

Model::~Model() {
}

void Model::play() {
    player->move();
}

Bundle& Model::getBundle() {
    bundle.position = player->getPosition();
    bundle.angle = player->getAngle();
    bundle.sector = scene->sectors;
    return bundle;
}


void Model::rotate(float rx, float ry) {
    player->rotate(rx, ry);
}

void Model::omitEvent(EVENTS event) {
    player->onKeyEvent(event);
}
