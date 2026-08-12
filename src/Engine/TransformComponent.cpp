#include "TransformComponent.hpp"

TransformComponent::TransformComponent() {
    transform = sf::Transform();
    position = sf::Vector2f(0, 0);
}

sf::Transform* TransformComponent::getTransform()
{
    return &transform;
}

sf::Vector2f TransformComponent::getPosition()
{
    return sf::Vector2f(x, y);
}

void TransformComponent::init()
{
}

void TransformComponent::update()
{
    position = sf::Vector2f(x, y);
}

void TransformComponent::draw()
{
    ImGui::Separator();
    Entity* ent = getEntity();
    if (ent) {
        ImGui::Text("Entity: %s", ent->GetName().c_str());
    }
    ImGui::DragFloat("X", &x, 1.0f);
    ImGui::DragFloat("Y", &y, 1.0f);
}
