#include "Inspector.hpp"
#include <cstddef>

Inspector::Inspector()
{
    curEntity_ = nullptr;
    name_ = "";
    SyncNameBuffer();
}

Inspector::Inspector(Entity& ent)
{
    name_ = ent.GetName();
    curEntity_ = &ent;
    SyncNameBuffer();
}

void Inspector::SyncNameBuffer()
{
    size_t n = name_.copy(nameBuf_, sizeof(nameBuf_) - 1);
    nameBuf_[n] = '\0';
}

void Inspector::Draw()
{
    ImGui::Begin("Inspector");

    if (curEntity_ != nullptr) {
        if (ImGui::InputText("Entity name", nameBuf_, sizeof(nameBuf_))) {
            name_ = nameBuf_;
            curEntity_->SetName(name_);
        }
        for (auto* c : curEntity_->GetComponents()) {
            ImGui::Text(c->GetName().data());
            c->draw();
        }
    } else {
        ImGui::InputTextWithHint("Empty name", "Entity name", nameBuf_, sizeof(nameBuf_), ImGuiInputTextFlags_ReadOnly);
    }

    ImGui::End();
}

void Inspector::SetEntity(Entity& ent)
{
    name_ = ent.GetName();
    curEntity_ = &ent;
    SyncNameBuffer();
}

void Inspector::PrintEntityName()
{
    std::cout << name_ << std::endl;
}
