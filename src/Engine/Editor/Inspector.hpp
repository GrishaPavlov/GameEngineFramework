#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include "../Entity.hpp"
#include "../Component.hpp"

class Inspector {
public:
    Inspector();
    Inspector(Entity &ent);
    void Draw();
    void SetEntity(Entity &ent);
    void PrintEntityName();
private:
    void SyncNameBuffer();
    std::string name_ = "";
    char nameBuf_[64] = {};
    Entity *curEntity_;
};
