#pragma once
#include <string>
#include <vector>
#include "Component.hpp"

class Entity {
    public:
    Entity(std::string name);
    void addComponent(const Component component);
    private:
    std::string name = "";
    std::vector<Component> components;
};