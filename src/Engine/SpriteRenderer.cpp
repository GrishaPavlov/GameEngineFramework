#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(const std::string& texturePath)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load: " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
}

void SpriteRenderer::init()
{
    sprite.setPosition(getObjectPosition());
}

void SpriteRenderer::update()
{
    sprite.setPosition(getObjectPosition());
}

sf::Vector2f SpriteRenderer::getObjectPosition()
{
    Entity* ent = getEntity();
    if (ent) {
        if (auto* tc = ent->GetComponent<TransformComponent>()) {
            return tc->getPosition();
        }
        return ent->getPosition();
    }
    return sf::Vector2f(0, 0);
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