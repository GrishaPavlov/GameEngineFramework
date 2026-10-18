#include "Renderer.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

Renderer::Renderer(sf::RenderWindow& w, Scene& sc, Editor& edit)
{
    window_ = &w;
    currentScene_ = &sc;
    editor_ = &edit;
}

void Renderer::Draw()
{
    if (!window_) {
        return;
    }

    window_->clear();

    drawScene();

    drawImGui();

    ImGui::SFML::Render(*window_);
    window_->display();
}

void Renderer::drawScene()
{
    if (!currentScene_) {
        return;
    }

    for (auto& entity : currentScene_->getEntities()) {
        if (auto* sprite = entity.GetComponent<SpriteRenderer>()) {
            sprite->drawTo(*window_);
        }
    }
}

void Renderer::drawImGui()
{
    if (editor_) {
        editor_->Draw();
    }
}
