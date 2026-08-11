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
    sf::Vector2f p = getPosition();
    ImGui::Text(std::to_string(p.x).c_str());
    ImGui::Text(std::to_string(p.y).c_str());
    Entity* ent = getEntity();
    if (ent) {
        ImGui::Text(ent->GetName().c_str());
    }
}
