#pragma once
#include <string>

class Component {
public:
    Component() = default;
    ~Component() = default;
    virtual void update() {};
    virtual void init() {};
private:
    std::string name;
};
