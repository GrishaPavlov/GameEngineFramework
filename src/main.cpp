#include "Engine/Component.hpp"
#include "Engine/Editor/Hierarchy.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Scene.hpp"
#include "Engine/SpriteRenderer.hpp"
#include "GamePlay/CounterComponent.hpp"
#include "Engine/TransformComponent.hpp"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <windows.h>
#include <filesystem>
#include <string>

static std::string ResolveTexturePath()
{
    wchar_t buf[MAX_PATH] = {};
    if (GetModuleFileNameW(nullptr, buf, MAX_PATH) != 0) {
        std::filesystem::path exeDir = std::filesystem::path(buf).parent_path();
        std::filesystem::path rel = exeDir / "../../../src/Sprites/test.png";
        return rel.lexically_normal().string();
    }
    return "C:/Users/Gregory/Projects/GameEngineFramework/src/Sprites/test.png";
}

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1280u, 720u }), "CMake SFML Project");
    window.setFramerateLimit(144);
    (void)ImGui::SFML::Init(window);

    Entity counter("Counter");
    CounterComponent* count = new CounterComponent(5);
    SpriteRenderer* spriteRend = new SpriteRenderer(ResolveTexturePath(), sf::Vector2f(200, 200));

    sf::RectangleShape box(sf::Vector2f(100.f, 100.f));
    box.setFillColor(sf::Color::White);
    box.setPosition(sf::Vector2f(100.f, 100.f));

    TransformComponent* transformcomp = new TransformComponent();
    counter.addComponent(transformcomp);
    counter.addComponent(count);
    counter.addComponent(spriteRend);
    counter.init();
    Scene test("Test");
    test.addObject(counter);
    Inspector insp;
    Hierarchy hierarchy(test, insp);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        test.update();
        hierarchy.Draw();
        insp.Draw();
        window.clear();
        window.draw(spriteRend->getSprite());
        window.draw(box);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
}
