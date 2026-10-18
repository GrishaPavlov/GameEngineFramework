# AGENTS.md

C++17 game engine (ECS-style) + ImGui editor demo. Single CMake executable named `main`. Windows/Visual Studio is the only environment in use.

## Build

- Configure: `cmake -S . -B build` (needs network + git on first run — SFML 3.0.1, ImGui v1.91.1, ImGui-SFML v3.0 are pulled via `FetchContent` into `build/_deps/`).
- Build: `cmake --build build --config Debug` (generator is Visual Studio 17 2022). Executable lands in `build/bin/<Config>/main.exe`.
- No tests, no lint, no CI. Verify changes by building.
- `build/` is gitignored; never commit it (its `_deps` are full dependency clones).

## The #1 trap: new source files are not picked up automatically

`CMakeLists.txt` lists every `.cpp` explicitly inside `add_executable(...)`. Adding `src/Engine/Foo.cpp` will compile only after you also add it there. Any new component requires: header + `.cpp` in `src/...`, entry in `CMakeLists.txt`.

## Adding a new Component

Every `Component` subclass (see `CounterComponent`, `SpriteRenderer`, `TransformComponent`) must:
- Override `GetRuntimeTypeID()` to return `Component::GetTypeID<MyComp>()` and override `GetName()`.
- `Component::GetTypeID<T>()` is the project's RTTI substitute (template static with atomic counter). Do not invent another ID scheme.
- Init/update/draw are no-op virtuals; `setEntity` back-pointer is set by `Entity::addComponent`.

## Ownership model (do not "fix" casually)

- `Entity` owns `std::vector<Component*>` raw pointers and has **no destructor** — components are deliberately leaked (see `main.cpp` which `new`s them).
- `Scene` stores `Entity` **by value**; `Scene::addObject(Entity)` and `operator=` shallow-copy. `addObject` re-attaches the stored copy's component back-pointers via `refreshComponentOwners()`, but any later reallocation of the scene vector leaves those pointers stale. Adding a destructor to `Entity` that deletes components would cause double-frees. Reworking this is a design decision, not a quick fix.
- `Entity::init()` calls `init()` on every component; call it after assembling an entity's components (see `main.cpp`).

## Windows-specific quirks

- `src/main.cpp` resolves `src/Sprites/test.png` relative to the executable location (`build/bin/<Config>/../../..` → repo root), so it works from any output dir without a hardcoded path.
- `imgui.ini` is committed and rewritten each run with UI layout state — an "unexpected" dirty diff there is normal.
- Working tree is currently a WIP feature branch (`customisable-sprite-renderer`); features are developed on branches and merged via PRs.

## Layout

- `src/Engine/` — core: `Component`, `Entity`, `Scene`, `Renderer`, `SpriteRenderer`, `TransformComponent`.
- `src/Engine/Editor/` — ImGui panels (`Hierarchy`, `Inspector`, `Editor`); they keep references to `Scene`/`Entity`.
- `src/GamePlay/` — gameplay sample components (e.g. `CounterComponent`).
- `src/main.cpp` is the real entrypoint; `src/Game.hpp` is scaffolding and unused.
