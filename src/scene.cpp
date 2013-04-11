#include "scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::load(Sector& walls)
{
    this->sectors = walls;
}
