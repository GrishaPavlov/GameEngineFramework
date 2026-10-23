#include "Hierarchy.hpp"
#include "../TransformComponent.hpp"
#include <string>

Hierarchy::Hierarchy(Scene& scn) : scene(scn), inspector(nullptr)
{
}

Hierarchy::Hierarchy(Scene& scn, Inspector& insp)
    : scene(scn), inspector(&insp)
{
}

void Hierarchy::Draw()
{
    ImGui::Begin("Hierarchy");

    if (ImGui::Button("Create Entity")) {
        Entity& ent = scene.createEntity("Entity " + std::to_string(nextEntityIndex_++));
        ent.addComponent<TransformComponent>();
        ent.init();
        if (inspector) {
            inspector->SetEntity(ent);
        }
    }
    ImGui::Separator();

    // Удалять прямо в цикле нельзя — это сломает итерацию по вектору,
    // поэтому запоминаем объект и удаляем его после цикла.
    Entity* toDelete = nullptr;
    auto& scene_entities = scene.getEntities();
    for (size_t i = 0; i < scene_entities.size(); ++i) {
        Entity* ent = scene_entities[i].get();
        // Объекты с одинаковыми именами иначе получили бы один и тот же ImGui ID.
        ImGui::PushID(ent);
        if (ImGui::Button(ent->GetName().c_str())) {
            if (inspector) {
                inspector->SetEntity(*ent);
            }
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Delete")) {
            toDelete = ent;
        }
        ImGui::PopID();
    }

    if (toDelete) {
        // Inspector держит сырой указатель — сбрасываем его до удаления.
        if (inspector && inspector->GetEntity() == toDelete) {
            inspector->ClearEntity();
        }
        scene.destroyEntity(*toDelete);
    }

    ImGui::End();
}

void Hierarchy::setInspector(Inspector& insp)
{
    inspector = &insp;
}
