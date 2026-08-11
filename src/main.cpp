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
    system("cd");
    auto window = sf::RenderWindow(sf::VideoMode({ 1280u, 720u }), "CMake SFML Project");
    window.setFramerateLimit(144);
    ImGui::SFML::Init(window);

    Entity counter("Counter");
    CounterComponent* count = new CounterComponent(5);
    SpriteRenderer* spriteRend = new SpriteRenderer(
        "C:/Users/Gregory/Projects/GameEngineFramework/src/Sprites/test.png",
         sf::Vector2f(200, 200)
        );


    auto& spr = spriteRend->getSprite();

std::cout << "Texture size: "
          << spr.getTexture().getSize().x << " x "
          << spr.getTexture().getSize().y << "\n";

std::cout << "Sprite position: "
          << spr.getPosition().x << ", " << spr.getPosition().y << "\n";

std::cout << "Sprite scale: "
          << spr.getScale().x << ", " << spr.getScale().y << "\n";

std::cout << "Sprite color: "
          << static_cast<int>(spr.getColor().r) << ", "
          << static_cast<int>(spr.getColor().g) << ", "
          << static_cast<int>(spr.getColor().b) << ", "
          << static_cast<int>(spr.getColor().a) << "\n";


sf::RectangleShape box(sf::Vector2f(100.f, 100.f));
box.setFillColor(sf::Color::White);
box.setPosition(sf::Vector2f(100.f, 100.f));
    // window.draw(spriteRend->getSprite());
    // SpriteRenderer* spriteRend = new SpriteRenderer();
    TransformComponent* transformcomp = new TransformComponent();
    sf::Texture textt = spriteRend->getCurrentTexture();
    counter.addComponent(transformcomp);
    counter.addComponent(count);
    counter.addComponent(spriteRend);
    Scene test("Test");
    test.addObject(counter);
    counter.DebugPrintComponents();
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
        window.draw(spriteRend->getSprite());
        window.draw(box);
        ImGui::SFML::Render(window);
        // window.draw(box);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
};