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
#include <filesystem>
#include <string>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#endif

static std::string ResolveTexturePath(const char* argv0)
{
    namespace fs = std::filesystem;
    const fs::path relative = fs::path("src") / "Sprites" / "test.png";
    std::error_code ec;

    fs::path exePath;
#if defined(_WIN32)
    wchar_t buf[MAX_PATH] = {};
    if (GetModuleFileNameW(nullptr, buf, MAX_PATH) != 0) {
        exePath = fs::path(buf);
    }
#else
    exePath = fs::read_symlink("/proc/self/exe", ec);
#endif
    if (exePath.empty() && argv0 && *argv0) {
        exePath = fs::absolute(argv0, ec);
    }

    // Search upwards from the executable directory, then the working directory,
    // so the path resolves both for single-config (build/bin) and multi-config
    // (build/bin/<Config>) layouts.
    std::vector<fs::path> bases;
    if (!exePath.empty()) {
        fs::path dir = exePath.parent_path();
        for (int i = 0; i < 4 && !dir.empty(); ++i) {
            bases.push_back(dir);
            dir = dir.parent_path();
        }
    }
    bases.push_back(fs::current_path(ec));

    for (const auto& base : bases) {
        const fs::path candidate = base / relative;
        if (fs::exists(candidate, ec)) {
            return fs::weakly_canonical(candidate, ec).string();
        }
    }

    return (fs::current_path(ec) / relative).string();
}

int main(int argc, char** argv)
{
    const char* argv0 = (argc > 0) ? argv[0] : nullptr;

    auto window = sf::RenderWindow(sf::VideoMode({ 1280u, 720u }), "CMake SFML Project");
    window.setFramerateLimit(144);
    (void)ImGui::SFML::Init(window);

    Scene test("Test");

    Entity& counter = test.createEntity("Counter");
    auto* transform = counter.addComponent<TransformComponent>();
    transform->position = { 200.f, 200.f };
    counter.addComponent<CounterComponent>(5);
    counter.addComponent<SpriteRenderer>(ResolveTexturePath(argv0));
    counter.init();

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

        const sf::Time dt = deltaClock.restart();
        ImGui::SFML::Update(window, dt);

        test.update(dt.asSeconds());

        renderer.Draw();
    }
    ImGui::SFML::Shutdown();

    return 0;
}
