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
    hasExplicitPosition_ = true;
    sprite.setPosition(sf::Vector2f(pos.x, pos.y));
}

void SpriteRenderer::init()
{
    Entity* ent = getEntity();
    if (!ent || hasExplicitPosition_) {
        return;
    }
    sprite.setPosition(ent->getPosition());
}

void SpriteRenderer::update()
{
}

void SpriteRenderer::draw()
{
    // The actual rendering happens via Renderer calling drawTo().
}

void SpriteRenderer::drawTo(sf::RenderTarget& target)
{
    target.draw(sprite);
}

void SpriteRenderer::setTexture(const std::string& path)
{
    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load: " << path << std::endl;
        return;
    }
    sprite.setTexture(texture);
}

sf::Texture SpriteRenderer::createEmptyTexture()
{
    return sf::Texture();
}