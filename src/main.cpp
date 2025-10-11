#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "GamePlay/CounterComponent.hpp"

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
        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
};