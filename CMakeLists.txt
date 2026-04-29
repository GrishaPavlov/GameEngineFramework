cmake_minimum_required(VERSION 3.10)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)
FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)
set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG v3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)

add_executable(main src/main.cpp
 src/Engine/Entity.cpp
 src/Engine/Component.cpp
 src/Engine/Scene.cpp
 src/Engine/Renderer.cpp
 src/Engine/SpriteRenderer.cpp
 src/Engine/TransformComponent.cpp
 src/GamePlay/CounterComponent.cpp
 src/Engine/Editor/Hierarchy.cpp
 src/Engine/Editor/Inspector.cpp
 src/Engine/Editor/Editor.cpp
 
 )
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

target_link_libraries(main PUBLIC ImGui-SFML::ImGui-SFML)
# set(IMGUI_DIR ${imgui_SOURCE_DIR})
# option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
# option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)

# FetchContent_MakeAvailable(imgui-sfml)