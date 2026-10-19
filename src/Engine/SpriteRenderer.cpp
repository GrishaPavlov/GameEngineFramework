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
    syncWithTransform();
}

void SpriteRenderer::update(float)
{
    syncWithTransform();
}

void SpriteRenderer::syncWithTransform()
{
    Entity* ent = getEntity();
    if (!ent) {
        return;
    }
    if (const auto* tc = ent->GetComponent<TransformComponent>()) {
        sprite.setPosition(tc->position);
        sprite.setRotation(sf::degrees(tc->rotation));
        sprite.setScale(tc->scale);
    }
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