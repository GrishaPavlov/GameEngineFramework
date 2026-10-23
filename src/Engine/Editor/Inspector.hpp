#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include "../Entity.hpp"
#include "../Component.hpp"
#include "../ComponentRegistry.hpp"

class Inspector {
public:
    Inspector();
    Inspector(Entity &ent);
    void Draw();
    void SetEntity(Entity &ent);
    void ClearEntity();
    Entity* GetEntity() const { return curEntity_; }
    void SetComponentRegistry(const ComponentRegistry& registry) { registry_ = &registry; }
    void PrintEntityName();
private:
    void SyncNameBuffer();
    void DrawAddComponentMenu();
    std::string name_ = "";
    char nameBuf_[64] = {};
    Entity *curEntity_;
    const ComponentRegistry* registry_ = nullptr;
};
