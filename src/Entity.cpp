#include "Entity.hpp"

Entity::Entity(std::string name) : name(name) {}

void Entity::addComponent(Component *Component) {
    components.push_back(Component);
};



void Entity::update() {
    for (auto& component : components) {
        component->update();
    }
}
