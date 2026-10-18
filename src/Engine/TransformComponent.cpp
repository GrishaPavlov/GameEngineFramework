#include "TransformComponent.hpp"

sf::Transform TransformComponent::getTransform() const
{
    sf::Transform transform;
    transform.translate(position);
    transform.rotate(sf::degrees(rotation));
    transform.scale(scale);
    return transform;
}

void TransformComponent::draw()
{
    ImGui::Separator();
    Entity* ent = getEntity();
    if (ent) {
        ImGui::Text("Entity: %s", ent->GetName().c_str());
    }
    ImGui::DragFloat2("Position", &position.x, 1.0f);
    ImGui::DragFloat("Rotation", &rotation, 1.0f);
    ImGui::DragFloat2("Scale", &scale.x, 0.01f);
}
