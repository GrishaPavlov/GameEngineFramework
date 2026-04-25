#include "Hierarchy.hpp"

// Hierarchy::Hierarchy(Scene& scn) : scene(scn) {
//     auto& scene_entities = scene.getEntities();  // Нужно реализовать getEntities()
//     for (size_t i = 0; i < scene_entities.size(); ++i) {
//         entities.push_back(&scene_entities[i]);
//     }
    
// }

Hierarchy::Hierarchy(Scene& scn, Inspector& insp) 
: scene(scn), inspector(insp)
{
    // entities = *scene.getEntities();
    auto& scene_entities = scene.getEntities();  // Нужно реализовать getEntities()
    std::cout<< scene.getEntities().size();
    for (size_t i = 0; i < scene_entities.size(); ++i) {
        entities.push_back(&scene_entities[i]);
    }
    inspector = insp;
}

void Hierarchy::Draw() {
    ImGui::Begin("Hierarchy");
    for (int i = 0; i < entities.size(); i++) {
        if (ImGui::Button(entities[i]->GetName().c_str())) {
            inspector.SetEntity( *entities[i]);
        }
    }
    ImGui::End();
}

void Hierarchy::setInspector(Inspector& insp)
{
    inspector = insp;
}
