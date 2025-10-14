#include "Editor.hpp"

Editor::Editor(Inspector &insp) { inspector_ = &insp; }

void Editor::SetInspector(Inspector &insp) { inspector_ = &insp; }

Inspector* Editor::GetInspector() { return inspector_; }
