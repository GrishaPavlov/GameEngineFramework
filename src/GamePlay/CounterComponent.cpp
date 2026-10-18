#include "CounterComponent.hpp"
#include <iostream>

CounterComponent::CounterComponent()
{
    counter = 0;
    
}

CounterComponent::CounterComponent(int c)
{
    counter = c;
}

void CounterComponent::init()
{
}

void CounterComponent::update()
{
    counter++;
    // if (counter % 10)
        // std::cout << counter << std::endl;
}

void CounterComponent::draw()
{
    ImGui::Separator();
    ImGui::Text(std::to_string(counter).c_str());
    Entity* ent = getEntity();
    if (ent) {
        ImGui::Text(ent->GetName().c_str());
    }
}
