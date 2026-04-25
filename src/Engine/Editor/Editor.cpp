#include "Editor.hpp"

Editor::Editor(Inspector& insp) { inspector_ = &insp; }

void Editor::SetHierarchy(Hierarchy& hier)
{
    hierarchy_ = &hier;
}

Hierarchy* Editor::GetHierarchy()
{
    return hierarchy_;
}

void Editor::SetInspector(Inspector& insp)
{
    inspector_ = &insp;
}

Inspector* Editor::GetInspector()
{
    return inspector_;
}
