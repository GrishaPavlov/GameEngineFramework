#pragma once
#include <string>

class Component {
public:
    Component();
    virtual void update();

private:
    std::string name;
};
