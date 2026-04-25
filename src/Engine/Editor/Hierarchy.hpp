#pragma once
#include "../Component.hpp"
#include "../Entity.hpp"
#include "../Scene.hpp"
#include "Inspector.hpp"

class Hierarchy {
public:
    Hierarchy(Scene& scn);
    Hierarchy(Scene& scn, Inspector& insp);
    void Draw();
    void setInspector(Inspector& insp);

private:
    Scene& scene;              // ← Ссылка!
    Inspector& inspector;
    std::vector<Entity*> entities;
};