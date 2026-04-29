#pragma once
#include <iostream>
#include "../Engine/Component.hpp"
#include "../Engine/Entity.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>


class SpriteRenderer : public Component
{
public:
    SpriteRenderer();
    sf::Texture& getCurrentTexture();
    void init() override;
    void update() override;
    void draw() override;
private:
    int counter;
    sf::Texture texture;
};