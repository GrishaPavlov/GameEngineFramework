#include "Component.hpp"
#include "Entity.hpp"

Component::Component() : name(""), entity(nullptr) {}


void Component::setEntity(Entity* ent)
{
    entity = ent;
}

Entity* Component::getEntity()
{
    return entity;
}