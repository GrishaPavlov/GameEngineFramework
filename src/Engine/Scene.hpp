#pragma once
#include <string>
#include "Entity.hpp"

class Scene {
public:
    Scene() = default;
    explicit Scene(std::string name) : name_(name) {};

    void addObject(Entity entity);
    void update();

private:
    std::string name_;
    std::vector<Entity> entities;
};
