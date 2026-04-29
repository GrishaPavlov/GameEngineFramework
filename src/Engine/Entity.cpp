#include "Entity.hpp"

Entity::Entity()
    : name("")
    , id_(0)
{
}

Entity::Entity(std::string name)
    : name(std::move(name))
{
    id_ = 0;
}

void Entity::addComponent(Component* comp)
{
    if (comp) { // ← 3. Проверка nullptr!
        comp->setEntity(this);
        components.push_back(comp);
    }
};

void Entity::update()
{
    for (auto& component : components) {
        component->update();
    }
}

void Entity::setId(uint8_t givenId)
{
    if (givenId >= 0)
        id_ = givenId;
}
