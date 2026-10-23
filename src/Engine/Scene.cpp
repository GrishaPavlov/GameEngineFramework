#include "Scene.hpp"
#include <algorithm>

Entity& Scene::createEntity(std::string name)
{
    return addObject(std::make_unique<Entity>(std::move(name)));
}

Entity& Scene::addObject(std::unique_ptr<Entity> entity)
{
    entities_.push_back(std::move(entity));
    return *entities_.back();
}

bool Scene::destroyEntity(Entity& entity)
{
    auto it = std::find_if(entities_.begin(), entities_.end(),
        [&entity](const std::unique_ptr<Entity>& e) { return e.get() == &entity; });
    if (it == entities_.end()) {
        return false;
    }
    entities_.erase(it);
    return true;
}

void Scene::update(float dt)
{
    for (auto& e : entities_)
    {
        e->update(dt);
    }
}
