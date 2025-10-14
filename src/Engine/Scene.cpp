#include "Scene.hpp"

void Scene::addObject(Entity entity)
{
    entities.push_back(entity);
}

void Scene::update()
{
    for (auto &e : entities)
    {
        e.update();
    }
}
