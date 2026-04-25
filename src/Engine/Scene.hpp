#pragma once
#include "Entity.hpp"
#include <string>
class Scene {
public:
    Scene() = default;  // Пустая сцена
    Scene(std::string name) : name_(std::move(name)), entities_() {}
    Scene(std::string name, std::vector<Entity> entities) 
        : name_(std::move(name)), entities_(std::move(entities)) {}
    
    Scene& Scene::operator=(const Scene& other);

    std::vector<Entity>& getEntities()
    {
        return entities_;
    }

    // Возвращает константную ссылку (для чтения)
    const std::vector<Entity>& getEntities() const
    {
        return entities_;    
    }

    void addObject(Entity entity);
    void update();
    ~Scene();

private:
    std::string name_;
    std::vector<Entity> entities_;
};
