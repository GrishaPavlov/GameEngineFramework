#pragma once
#include "Component.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

class Entity {
public:
    Entity();
    Entity(std::string name);

    // Компоненты хранят обратный указатель на Entity, поэтому Entity нельзя
    // копировать или перемещать — она живёт по стабильному адресу (в Scene).
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(Entity&&) = delete;

    Component* addComponent(std::unique_ptr<Component> comp);

    template <typename T, typename... Args>
    T* addComponent(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = comp.get();
        addComponent(std::move(comp));
        return raw;
    }

    void init();
    void update();
    void setId(uint16_t);
    void SetName(const std::string& newName) { name = newName; }
    const std::vector<std::unique_ptr<Component>>& GetComponents() const { return components; }
    std::string GetName() { return name; };
    void PrintComponents();
    void DebugPrintComponents() const;

    template <typename T>
    T* GetComponent()
    {
        for (auto& comp : components) {
            if (comp && Component::GetTypeID<T>() == comp->GetRuntimeTypeID()) {
                return static_cast<T*>(comp.get());
            }
        }
        return nullptr;
    }

    template <typename T>
    const T* GetComponent() const
    {
        for (auto& comp : components) {
            if (comp && comp->GetRuntimeTypeID() == Component::GetTypeID<T>()) {
                return static_cast<const T*>(comp.get());
            }
        }
        return nullptr;
    }

    template <typename T>
    bool HasComponent() const
    {
        return GetComponent<T>() != nullptr;
    }

private:
    uint16_t id_ = 0;
    std::string name = "";
    std::vector<std::unique_ptr<Component>> components;
};
