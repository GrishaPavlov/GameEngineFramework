#pragma once
#include <iostream>
#include "../Engine/Component.hpp"
#include "../Engine/Entity.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>


class TransformComponent : public Component
{
public:
    TransformComponent();
    sf::Transform* getTransform();
    void init() override;
    void update() override;
    void draw() override;
private:
    sf::Transform transform;
    sf::Vector2f position = sf::Vector2f(0, 0);
};