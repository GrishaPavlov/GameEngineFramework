#include <SFML/Graphics.hpp>
#include "Engine/Scene.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Component.hpp"
#include "GamePlay/CounterComponent.hpp"
#include "Engine/Editor/Hierarchy.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    ImGui::SFML::Init(window);

    Entity counter("Counter");
    CounterComponent *count = new CounterComponent(5);
    counter.addComponent(count);
    Scene test("Test");
    test.addObject(counter);
    Inspector insp;
    Hierarchy hierarchy(test, insp);

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
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
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
};