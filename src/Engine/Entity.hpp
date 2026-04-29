#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "Component.hpp"

class Entity {
public:
    Entity();
    Entity(std::string name);
    void addComponent(Component *comp);
    void update();
    void setId(uint8_t);
    std::vector<Component *>& GetComponents() { return components; }
    std::string GetName() { return name; };

private:
    uint16_t id_ = 0;
    std::string name = "";
    std::vector<Component *> components;
};
