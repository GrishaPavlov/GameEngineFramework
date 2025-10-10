#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "GamePlay/CounterComponent.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    Entity counter("Counter");
    CounterComponent *count = new CounterComponent(5);
    counter.addComponent(count);
    Scene test("Test");
    test.addObject(counter);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
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
        test.update();
        window.clear();
        window.display();
    }
    return 0;
};