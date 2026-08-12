#include "Engine/SpriteRenderer.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/Editor/Editor.hpp"
#include "Engine/Editor/Hierarchy.hpp"
#include "Engine/Editor/Inspector.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Scene.hpp"
#include "Engine/Entity.hpp"
#include "GamePlay/CounterComponent.hpp"
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
    SpriteRenderer* spriteRend = new SpriteRenderer(ResolveTexturePath());
    TransformComponent* transformcomp = new TransformComponent();
    transformcomp->x = 200;
    transformcomp->y = 200;

    counter.addComponent(transformcomp);
    counter.addComponent(count);
    counter.addComponent(spriteRend);
    counter.init();

    Scene test("Test");
    test.addObject(counter);

    Inspector insp;
    Hierarchy hierarchy(test, insp);
    Editor editor(insp);
    editor.SetHierarchy(hierarchy);

    Renderer renderer(window, test, editor);

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

        test.update();

        renderer.Draw();
    }
    ImGui::SFML::Shutdown();

    return 0;
}
