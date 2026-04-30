cmake_minimum_required(VERSION 3.16)
project(TRIGAEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# MSVC Compiler Options
if(MSVC)
    add_compile_options(/W3 /WX- /permissive-)
endif()

# Find required packages
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

# Fetch dependencies
include(FetchContent)

# GLFW - Window management
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
)

# GLM - Math library
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
    GIT_SHALLOW TRUE
)

# spdlog - Logging
FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
    GIT_SHALLOW TRUE
)

# ImGui - UI framework
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.7
    GIT_SHALLOW TRUE
)

# Make all dependencies available
FetchContent_MakeAvailable(glfw glm spdlog imgui)

# Create executable - ONLY main.cpp
add_executable(triga_editor 
    src/main.cpp
)

# Include directories
target_include_directories(triga_editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}
    ${imgui_SOURCE_DIR}
    ${spdlog_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(triga_editor PRIVATE
    glfw
    OpenGL::GL
    spdlog::spdlog
    Threads::Threads
)

# Windows-specific settings
if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set_target_properties(triga_editor PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
endif()

# Installation
install(TARGETS triga_editor RUNTIME DESTINATION bin)

message(STATUS "======================================")
message(STATUS "TRIGA Engine Build Configuration")
message(STATUS "======================================")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "======================================")
