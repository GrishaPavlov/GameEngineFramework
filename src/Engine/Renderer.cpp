#include "Renderer.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

Renderer::Renderer(sf::RenderWindow &w, Scene &sc, Editor &edit) {
    window_ = &w;
    currentScene_ = &sc;
    editor_ = &edit;
}


void Renderer::Draw() {
    // window_->clear();

    if (editor_ && editor_->GetInspector()) {
        editor_->GetInspector()->Draw();
    }
    // ImGui::SFML::Render(*window_);
    // window_->display();
}




