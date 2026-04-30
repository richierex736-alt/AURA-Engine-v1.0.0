cmake_minimum_required(VERSION 3.16)
project(TRIGAEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
    add_compile_options(/W4 /WX-)
endif()

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG v1.91.7)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.1)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.12.0)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git GIT_TAG main)
FetchContent_MakeAvailable(glad)

FetchContent_Declare(stb GIT_REPOSITORY https://github.com/nothings/stb.git GIT_TAG master)
FetchContent_MakeAvailable(stb)

add_executable(triga_editor 
    src/editor/main.cpp
    src/core/Core.cpp
    src/core/Entity.cpp
    src/core/Logger.cpp
    src/core/Scene.cpp
    src/core/Types.cpp
    src/core/Window.cpp
    src/core/Input.cpp
    src/editor/Editor.cpp
    src/editor/EditorPanels.cpp
    src/editor/Gizmo.cpp
    src/editor/Hotkeys.cpp
    src/editor/MaterialEditor.cpp
    src/editor/SculptPanel.cpp
    src/editor/UVEditor.cpp
    src/editor/UndoRedo.cpp
    src/render/Framebuffer.cpp
    src/render/Light.cpp
    src/render/Material.cpp
    src/render/Mesh.cpp
    src/render/Renderer.cpp
    src/render/Shader.cpp
    src/render/Terrain.cpp
    src/render/Texture.cpp
    src/physics/Collider.cpp
    src/physics/Joint.cpp
    src/physics/PhysicsWorld.cpp
    src/physics/RigidBody.cpp
    src/ai/BehaviorTree.cpp
    src/animation/Animation.cpp
    src/assets/AssetManager.cpp
    src/serialization/SceneSerialization.cpp
    src/vfx/VFXGraph.cpp
    src/sculpt/Sculpt.cpp
)

target_include_directories(triga_editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}
    ${imgui_SOURCE_DIR}
    ${spdlog_SOURCE_DIR}/include
    ${glad_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
)

target_link_libraries(triga_editor PRIVATE
    glfw
    OpenGL::GL
    imgui
    spdlog::spdlog
    glad
    Threads::Threads
)

if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set_target_properties(triga_editor PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
endif()

install(TARGETS triga_editor RUNTIME DESTINATION bin)

message(STATUS "TRIGA Engine configured")
