#pragma once
#include "Inspector.hpp"

// Тут будут добавляться другие элементы редактора (Просмотр иерархии сцены как пример)
class Editor {
public:
    Editor() = default;
    Editor(Inspector &insp);
    void SetInspector(Inspector &insp);
    Inspector* GetInspector();

private:
    Inspector *inspector_;
};
