#include "CounterComponent.hpp"
#include <iostream>

CounterComponent::CounterComponent()
{
    counter = 0;
    
}

CounterComponent::CounterComponent(int c)
{
    counter = static_cast<float>(c);
}

void CounterComponent::init()
{
}

void CounterComponent::update(float dt)
{
    counter += dt;
    // if (counter % 10)
        // std::cout << counter << std::endl;
}

void CounterComponent::draw()
{
    ImGui::Separator();
    ImGui::Text("Counter: %.2f s", counter);
    Entity* ent = getEntity();
    if (ent) {
        ImGui::TextUnformatted(ent->GetName().c_str());
    }
}
