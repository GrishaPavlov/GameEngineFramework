#pragma once
#include "../Engine/Component.hpp"
#include "../Engine/Entity.hpp"
#include "TransformComponent.hpp"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

class SpriteRenderer : public Component {
public:
    SpriteRenderer() = default;
    SpriteRenderer(const std::string& texturePath);
    SpriteRenderer(const std::string& texturePath, sf::Vector2f pos);
    void init() override;
    void update() override;
    void draw() override;

    void drawTo(sf::RenderTarget& target);
    sf::Texture& getCurrentTexture() { return texture; };
    const sf::Sprite& getSprite() const { return sprite; }
    void setTexture(const std::string& path);

    std::string GetName() const override { return "Sprite Renderer"; }

    uint32_t GetRuntimeTypeID() const override
    {
        return Component::GetTypeID<SpriteRenderer>();
    }

private:
    sf::Texture createEmptyTexture();

    sf::Texture texture;
    sf::Sprite sprite { texture };

    bool hasExplicitPosition_ = false;
    sf::Vector2f relativePosition = sf::Vector2f(0, 0);
};