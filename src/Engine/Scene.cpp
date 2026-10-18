#include "Scene.hpp"

Entity& Scene::createEntity(std::string name)
{
    return addObject(std::make_unique<Entity>(std::move(name)));
}

Entity& Scene::addObject(std::unique_ptr<Entity> entity)
{
    entities_.push_back(std::move(entity));
    return *entities_.back();
}

void Scene::update()
{
    for (auto& e : entities_)
    {
        e->update();
    }
}
