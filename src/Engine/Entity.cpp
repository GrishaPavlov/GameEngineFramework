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

void Entity::update()
{
    for (auto& component : components) {
        component->update();
    }
}

void Entity::setId(uint8_t givenId)
{
    if (givenId >= 0)
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
    std::cout << "lalala" << std::endl;
    for (size_t i = 0; i < components.size(); ++i) {
        std::cout << "Index " << i << ": " << components[i]->GetName() << std::endl;
    }
}