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
        // Удалять прямо в цикле нельзя — это сломает итерацию по вектору,
        // поэтому запоминаем компонент и удаляем его после цикла.
        Component* toRemove = nullptr;
        for (auto& c : curEntity_->GetComponents()) {
            // Уникальный ID для каждого компонента, чтобы одинаковые подписи
            // (например, "Position") в разных компонентах не конфликтовали.
            ImGui::PushID(c.get());
            ImGui::TextUnformatted(c->GetName().c_str());
            ImGui::SameLine();
            if (ImGui::SmallButton("Remove")) {
                toRemove = c.get();
            }
            if (auto* sr = dynamic_cast<SpriteRenderer*>(c.get())) {
                const auto& t = sr->getCurrentTexture();
                if (t.getSize().x > 0 && t.getSize().y > 0) {
                    ImGui::Text("Texture: %ux%u", t.getSize().x, t.getSize().y);
                    ImGui::Image(t, sf::Vector2f(64.f, 64.f));
                } else {
                    ImGui::Text("Texture: (empty)");
                }
            }
            c->draw();
            ImGui::PopID();
        }
        if (toRemove) {
            curEntity_->removeComponent(toRemove);
        }

        DrawAddComponentMenu();
    } else {
        ImGui::InputTextWithHint("Empty name", "Entity name", nameBuf_, sizeof(nameBuf_), ImGuiInputTextFlags_ReadOnly);
    }

    ImGui::End();
}

void Inspector::DrawAddComponentMenu()
{
    if (!registry_) {
        return;
    }

    ImGui::Separator();
    if (ImGui::Button("Add Component")) {
        ImGui::OpenPopup("AddComponentPopup");
    }
    if (ImGui::BeginPopup("AddComponentPopup")) {
        for (const auto& entry : registry_->GetEntries()) {
            // Не больше одного компонента каждого типа: GetComponent<T>()
            // всё равно видит только первый.
            const bool alreadyAdded = curEntity_->HasComponentOfType(entry.typeId);
            if (ImGui::Selectable(entry.name.c_str(), false,
                    alreadyAdded ? ImGuiSelectableFlags_Disabled : 0)) {
                if (Component* comp = curEntity_->addComponent(entry.create())) {
                    comp->init();
                }
            }
        }
        ImGui::EndPopup();
    }
}

void Inspector::SetEntity(Entity& ent)
{
    name_ = ent.GetName();
    curEntity_ = &ent;
    SyncNameBuffer();
}

void Inspector::ClearEntity()
{
    name_ = "";
    curEntity_ = nullptr;
    SyncNameBuffer();
}

void Inspector::PrintEntityName()
{
    std::cout << name_ << std::endl;
}
