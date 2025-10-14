#include "Entity.hpp"

Entity::Entity() {
    name = "";
    id_ = NULL;
}

Entity::Entity(std::string name) : name(name) {}

void Entity::addComponent(Component *Component) { components.push_back(Component); };


void Entity::update() {
    for (auto &component: components) {
        component->update();
    }
}

void Entity::setId(uint8_t givenId) {
    if (givenId >= 0)
        id_ = givenId;
}
