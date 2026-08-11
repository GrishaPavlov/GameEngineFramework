#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(const std::string& texturePath)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load: " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
}

SpriteRenderer::SpriteRenderer(const std::string& texturePath, sf::Vector2f pos)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load: " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
    // sf::Vector2f transform = getEntity()->getPosition();
    sprite.setPosition(sf::Vector2f(pos.x, pos.y));
}

void SpriteRenderer::init()
{
    sf::Vector2f transform = getEntity()->getPosition();
    sprite.setPosition(sf::Vector2f(transform.x, transform.y));
}

void SpriteRenderer::update()
{
}

void SpriteRenderer::draw()
{
    // std::cout<<"I'm drawing"<<"/n";
}

void SpriteRenderer::setTexture(const std::string& path)
{
}

sf::Texture SpriteRenderer::createEmptyTexture()
{
    return sf::Texture();
}