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

Component* Entity::addComponent(std::unique_ptr<Component> comp)
{
    if (!comp) {
        return nullptr;
    }
    comp->setEntity(this);
    components.push_back(std::move(comp));
    return components.back().get();
}

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
    for (auto& component : components) {
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

void Entity::setId(uint16_t givenId)
{
    id_ = givenId;
}

void Entity::DebugPrintComponents() const {
    std::cout << "Entity '" << name << "' components (" << components.size() << "):\n";
    
    for (size_t i = 0; i < components.size(); ++i) {
        const auto& comp = components[i];
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