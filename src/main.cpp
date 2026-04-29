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

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "CMake SFML Project");
    window.setFramerateLimit(144);
    ImGui::SFML::Init(window);

    Entity counter("Counter");
    CounterComponent* count = new CounterComponent(5);
    SpriteRenderer* spriteRend = new SpriteRenderer();
    TransformComponent* transformcomp = new TransformComponent();
    sf::Texture textt = spriteRend->getCurrentTexture();
    counter.addComponent(spriteRend);
    counter.addComponent(count);
    counter.addComponent(transformcomp);
    Scene test("Test");
    test.addObject(counter);
    Inspector insp;
    Hierarchy hierarchy(test, insp);

    // sf::RectangleShape box(sf::Vector2f(100.0f, 100.0f)); // Size: 100x100
    // box.setFillColor(sf::Color::White); // Set color to white
    // box.setPosition(sf::Vector2f(0.0f, 0.0f)); // Center it

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
        sf::Sprite sprite(textt);
        sprite.setPosition(sf::Vector2f(100, 100));
        window.draw(sprite);
        ImGui::SFML::Render(window);
        // window.draw(box);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
};