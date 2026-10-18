#include "Entity.hpp"

Entity::Entity()
    : name("")
    , id_(0)
{
}

Entity::Entity(std::string name)
    : name(std::move(name))
{
    id_ = 0;
}

void Entity::addComponent(Component* comp)
{
    if (comp) { // ← 3. Проверка nullptr!
        comp->setEntity(this);
        components.push_back(comp);
    }
};

// template<typename T>
// const T* Entity::GetComponent() const {
//     uint32_t targetID = Component::GetTypeID<T>();
//     for (auto* comp : components) {
//         if (comp && comp->GetRuntimeTypeID() == targetID) {
//             return dynamic_cast<const T*>(comp);
//         }
//     }
//     return nullptr;
// }

void Entity::init()
{
    for (auto* component : components) {
        if (component) {
            component->init();
        }
    }
}

void Entity::update()
{
    for (auto& component : components) {
        component->update();
    }
}

void Entity::refreshComponentOwners()
{
    for (auto* component : components) {
        if (component) {
            component->setEntity(this);
        }
    }
}

void Entity::setId(uint16_t givenId)
{
    id_ = givenId;
}

void Entity::DebugPrintComponents() const {
    std::cout << "Entity '" << name << "' components (" << components.size() << "):\n";
    
    for (size_t i = 0; i < components.size(); ++i) {
        auto* comp = components[i];
        if (comp) {
            std::cout << "  [" << i << "] " << comp->GetName() 
                      << " (ID: " << comp->GetRuntimeTypeID() << ")\n";
        } else {
            std::cout << "  [" << i << "] NULL\n";
        }
    }
}

void Entity::PrintComponents()
{
    for (size_t i = 0; i < components.size(); ++i) {
        if (components[i]) {
            std::cout << "[" << i << "] " << components[i]->GetName() << std::endl;
        }
    }
}