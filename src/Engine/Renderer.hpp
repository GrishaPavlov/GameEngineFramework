#pragma once
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include "Scene.hpp"
#include "SpriteRenderer.hpp"
#include "Editor/Editor.hpp"
class Renderer {
public:
    Renderer(sf::RenderWindow& w, Scene& sc, Editor& edit);
    void Draw();
    void drawScene();
private:
    void drawImGui();
    sf::RenderWindow* window_;
    Scene* currentScene_;
    Editor* editor_;
};
