#include "Inspector.hpp"
#include "../SpriteRenderer.hpp"
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
            if (auto* sr = dynamic_cast<SpriteRenderer*>(c)) {
                const auto& t = sr->getCurrentTexture();
                if (t.getSize().x > 0 && t.getSize().y > 0) {
                    ImGui::Text("Texture: %ux%u", t.getSize().x, t.getSize().y);
                    ImGui::Image(t, sf::Vector2f(64.f, 64.f));
                } else {
                    ImGui::Text("Texture: (empty)");
                }
            }
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
