#include "Entity.hpp"

Entity::Entity(std::string name) {
    this->name = name;
}

void Entity::addComponent(const Component component) { components.push_back(component); }
