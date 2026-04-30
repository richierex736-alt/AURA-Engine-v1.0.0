#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>
#include <set>

namespace triga {

class Input {
public:
    static void Initialize(GLFWwindow* window);
    static void Update();

    static bool IsKeyDown(int key);
    static bool IsKeyPressed(int key);
    static bool IsKeyReleased(int key);

    static bool IsMouseButtonDown(int button);
    static bool IsMouseButtonPressed(int button);
    static bool IsMouseButtonReleased(int button);

    static glm::vec2 GetMousePosition();
    static glm::vec2 GetMouseDelta();
    static float GetMouseScroll();

    static void SetMousePosition(double x, double y);
    static void SetMouseCaptured(bool captured);
    static bool IsMouseCaptured();

    static void SetCursorVisible(bool visible);

private:
    static GLFWwindow* s_window;
    static std::map<int, bool> s_currentKeys;
    static std::map<int, bool> s_previousKeys;
    static std::map<int, bool> s_currentMouseButtons;
    static std::map<int, bool> s_previousMouseButtons;
    static glm::vec2 s_mousePosition;
    static glm::vec2 s_previousMousePosition;
    static float s_mouseScroll;
    static bool s_mouseCaptured;
};

} // namespace triga
