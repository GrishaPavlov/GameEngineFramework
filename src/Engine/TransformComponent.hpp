#pragma once
#include "../Engine/Component.hpp"
#include "../Engine/Entity.hpp"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

// Единственный источник положения объекта в мире.
class TransformComponent : public Component {
public:
    TransformComponent() = default;
    sf::Transform getTransform() const;
    sf::Vector2f getPosition() const { return position; }
    void draw() override;

    std::string GetName() const override { return "Transform"; }

    uint32_t GetRuntimeTypeID() const override
    {
        return Component::GetTypeID<TransformComponent>(); // ← Вызываем шаблон!
    }

    sf::Vector2f position { 0.f, 0.f };
    float rotation = 0.f; // градусы
    sf::Vector2f scale { 1.f, 1.f };
};
