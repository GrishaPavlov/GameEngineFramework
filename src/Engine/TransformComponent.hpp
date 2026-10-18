#pragma once
#include "../Engine/Component.hpp"
#include "../Engine/Entity.hpp"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

class TransformComponent : public Component {
public:
    TransformComponent();
    sf::Transform* getTransform();
    sf::Vector2f getPosition();
    void init() override;
    void update() override;
    void draw() override;

    std::string GetName() const override { return "Transform"; }

    uint32_t GetRuntimeTypeID() const override
    {
        return Component::GetTypeID<TransformComponent>(); // ← Вызываем шаблон!
    }

    float x = 0;
    float y = 0;

private:
    sf::Transform transform;
    sf::Vector2f position = sf::Vector2f(0, 0);
};