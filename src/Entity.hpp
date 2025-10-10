#pragma once
#include <string>
#include <vector>
#include "Component.hpp"
class Entity
{
public:
    Entity(std::string name);
    void addComponent(Component *Component);
    void update();

private:
    std::string name = "";
    std::vector<Component *> components; 
};