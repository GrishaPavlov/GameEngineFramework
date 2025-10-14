#pragma once
#include <string>

class Component {
public:
    Component() = default;
    ~Component() = default;
    virtual void update() {};
    virtual void init() {};
    virtual void draw() {};
    virtual std::string GetName() { return "";};
private:
    std::string name;
};
