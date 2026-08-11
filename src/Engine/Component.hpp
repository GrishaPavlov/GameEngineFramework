#pragma once
#include <string>
#include <cstdint>
#include <atomic>
// #include "Entity.hpp"
class Entity;

class Component {
public:
    Component();
    ~Component() = default;
    void setEntity(Entity* ent);
    Entity* getEntity();
    virtual void update() { };
    virtual void init() { };
    virtual void draw() { };


    virtual std::string GetName() const { return name; };
    template<typename T>
    static uint32_t GetTypeID() {
        static uint32_t id = nextID++;
        return id;
    }
    
    virtual uint32_t GetRuntimeTypeID() const = 0;

private:
    static std::atomic<uint32_t> nextID;
    std::string name;
    Entity* entity = nullptr;
};
