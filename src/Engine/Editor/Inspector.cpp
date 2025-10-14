#include "Inspector.hpp"

Inspector::Inspector() {
    curEntity_ = nullptr;
    // components_ = nullptr;
    name_ = "";
}

Inspector::Inspector(Entity &ent) {
    name_ = ent.GetName();
    curEntity_ = &ent;
}

void Inspector::Draw() {
    ImGui::Begin("Inspector");

    if (curEntity_ != nullptr) {
        ImGui::InputText("Entity name", name_.data(), 64);
    } else {
        ImGui::InputTextWithHint("Empty name", "Entity name", name_.data(), 64, ImGuiInputTextFlags_ReadOnly);
    }

    for (auto *c: curEntity_->GetComponents()) {
        ImGui::SeparatorText(c->GetName().data());
        c->draw();
    }

    ImGui::End();
}

void Inspector::SetEntity(Entity &ent) {
    name_ = ent.GetName();
    curEntity_ = &ent;
}

void Inspector::PrintEntityName() {
    std::cout << name_ << std::endl;
}
