#include "Hierarchy.hpp"

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
    auto& scene_entities = scene.getEntities();
    for (size_t i = 0; i < scene_entities.size(); ++i) {
        // Объекты с одинаковыми именами иначе получили бы один и тот же ImGui ID.
        ImGui::PushID(scene_entities[i].get());
        if (ImGui::Button(scene_entities[i]->GetName().c_str())) {
            if (inspector) {
                inspector->SetEntity(*scene_entities[i]);
            }
        }
        ImGui::PopID();
    }
    ImGui::End();
}

void Hierarchy::setInspector(Inspector& insp)
{
    inspector = &insp;
}
