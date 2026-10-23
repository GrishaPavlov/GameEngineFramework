#pragma once
#include "Component.hpp"
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Список компонентов, которые редактор может добавить на объект.
// Движок не знает про игровые компоненты, поэтому их регистрируют снаружи (в main.cpp).
class ComponentRegistry {
public:
    using Factory = std::function<std::unique_ptr<Component>()>;

    struct Entry {
        std::string name;
        uint32_t typeId;
        Factory create;
    };

    template <typename T>
    void Register(std::string name)
    {
        Register<T>(std::move(name), [] { return std::make_unique<T>(); });
    }

    // Своя фабрика нужна, если у компонента нет осмысленного конструктора
    // по умолчанию (например, SpriteRenderer без текстуры ничего не рисует).
    template <typename T>
    void Register(std::string name, Factory factory)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
        entries_.push_back({ std::move(name), Component::GetTypeID<T>(), std::move(factory) });
    }

    const std::vector<Entry>& GetEntries() const { return entries_; }

private:
    std::vector<Entry> entries_;
};
