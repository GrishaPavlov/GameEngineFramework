#pragma once
#include "../Engine/Component.hpp"
#include "../Engine/Entity.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

class CounterComponent : public Component
{
public:
    CounterComponent();
    CounterComponent(int c);
    ~CounterComponent();
    void init() override;
    void update() override;
    void draw() override;
private:
    int counter;
};