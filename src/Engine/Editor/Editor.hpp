#pragma once
#include "Inspector.hpp"
#include "Hierarchy.hpp"
// Тут будут добавляться другие элементы редактора (Просмотр иерархии сцены как пример)
class Editor {
public:
    Editor() = default;
    Editor(Inspector &insp);
    
    void SetHierarchy(Hierarchy &hier);
    Hierarchy* GetHierarchy();

    void SetInspector(Inspector &insp);
    Inspector* GetInspector();
    
private:
    Inspector *inspector_;
    Hierarchy *hierarchy_;
};
