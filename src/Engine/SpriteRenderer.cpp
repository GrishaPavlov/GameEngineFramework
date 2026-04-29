#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer()
{
    counter = 0;
    if (!texture.loadFromFile("src/Sprites/test.png", false, sf::IntRect({ 100, 100 }, { 320, 320 }))) {
        std::cout << "fuck" << std::endl;
    }
}

sf::Texture& SpriteRenderer::getCurrentTexture()
{
    return texture;
}

void SpriteRenderer::init()
{
}

void SpriteRenderer::update()
{
}

void SpriteRenderer::draw()
{
}
