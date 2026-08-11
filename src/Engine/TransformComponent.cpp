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
    return position;
}

void TransformComponent::init()
{

}

void TransformComponent::update()
{
}

void TransformComponent::draw()
{
      ImGui::Separator();                               
    ImGui::Text(std::to_string(position.x).c_str());
    ImGui::Text(std::to_string(position.y).c_str());
    ImGui::Text(Component::getEntity()->GetName().c_str());
}
