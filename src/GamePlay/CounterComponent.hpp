#pragma once
#include "../Component.hpp"
#include "../Entity.hpp"
class CounterComponent : public Component
{
public:
    CounterComponent();
    CounterComponent(int c);
    ~CounterComponent();
    void init() override;
    void update() override;
private:
    int counter;
};