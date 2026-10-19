#pragma once
#include "Entity.hpp"
#include <memory>
#include <string>
#include <vector>

class Scene {
public:
    Scene() = default;  // Пустая сцена
    Scene(std::string name) : name_(std::move(name)), entities_() {}

    // Сцена владеет объектами через unique_ptr: адреса Entity стабильны,
    // даже когда вектор перевыделяется, поэтому указатели на них
    // (из компонентов и редактора) не протухают.
    std::vector<std::unique_ptr<Entity>>& getEntities()
    {
        return entities_;
    }

    // Возвращает константную ссылку (для чтения)
    const std::vector<std::unique_ptr<Entity>>& getEntities() const
    {
        return entities_;    
    }

    Entity& createEntity(std::string name);
    Entity& addObject(std::unique_ptr<Entity> entity);
    void update(float dt);

private:
    std::string name_;
    std::vector<std::unique_ptr<Entity>> entities_;
};
