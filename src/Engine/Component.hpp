#pragma once
#include <string>
// #include "Entity.hpp"
class Entity;

class Component {
public:
    Component();
    ~Component() = default;
    void setEntity(Entity* ent);
    Entity* getEntity();
    virtual void update() {};
    virtual void init() {};
    virtual void draw() {};
    virtual std::string GetName() const { return name;};
private:
    std::string name;
    Entity* entity = nullptr;
};
