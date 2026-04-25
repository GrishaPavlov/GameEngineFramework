#include "Scene.hpp"


Scene& Scene::operator=(const Scene& other)
{
    name_ = other.name_;
    entities_ = other.entities_;
    
    return *this;
}



// template <typename T>
void Scene::addObject(Entity entity)
{
    entities_.push_back(entity);
}

void Scene::update()
{
    for (auto &e : entities_)
    {
        e.update();
    }
}

Scene::~Scene()
{
    
}
