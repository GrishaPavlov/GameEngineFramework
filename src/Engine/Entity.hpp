#pragma once
#include "Component.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics/Transformable.hpp>

class Entity : public sf::Transformable{
public:
    Entity();
    Entity(std::string name);
    void addComponent(Component* comp);
    void update();
    void setId(uint8_t);
    std::vector<Component*>& GetComponents() { return components; }
    std::string GetName() { return name; };
    void PrintComponents();
    void DebugPrintComponents() const;

    template <typename T>
    T* GetComponent()
    {
        for (auto* comp : components) {
            if (comp && Component::GetTypeID<T>() == comp->GetRuntimeTypeID()) {
                return dynamic_cast<T*>(comp);
            }
        }
        return nullptr;
    }

    template <typename T>
    const T* GetComponent() const
    {
        for (auto* comp : components) {
            if (comp && comp->GetRuntimeTypeID() == Component::GetTypeID<T>()) {
                return dynamic_cast<const T*>(comp);
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
    std::vector<Component*> components;
};
