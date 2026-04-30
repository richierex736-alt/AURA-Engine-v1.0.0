#include "triga/core/Input.h"
#include <GLFW/glfw3.h>

namespace triga {

GLFWwindow* Input::s_window = nullptr;
std::map<int, bool> Input::s_currentKeys;
std::map<int, bool> Input::s_previousKeys;
std::map<int, bool> Input::s_currentMouseButtons;
std::map<int, bool> Input::s_previousMouseButtons;
glm::vec2 Input::s_mousePosition(0.0f);
glm::vec2 Input::s_previousMousePosition(0.0f);
float Input::s_mouseScroll = 0.0f;
bool Input::s_mouseCaptured = false;

void Input::Initialize(GLFWwindow* window) {
    s_window = window;
}

void Input::Update() {
    s_previousKeys = s_currentKeys;
    s_previousMouseButtons = s_currentMouseButtons;
    s_previousMousePosition = s_mousePosition;

    if (s_window) {
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) {
            s_currentKeys[key] = glfwGetKey(s_window, key) == GLFW_PRESS;
        }

        for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; button++) {
            s_currentMouseButtons[button] = glfwGetMouseButton(s_window, button) == GLFW_PRESS;
        }

        double x, y;
        glfwGetCursorPos(s_window, &x, &y);
        s_mousePosition = glm::vec2(static_cast<float>(x), static_cast<float>(y));
    }
}

bool Input::IsKeyDown(int key) {
    auto it = s_currentKeys.find(key);
    return it != s_currentKeys.end() && it->second;
}

bool Input::IsKeyPressed(int key) {
    bool current = IsKeyDown(key);
    auto it = s_previousKeys.find(key);
    bool previous = (it != s_previousKeys.end() && it->second);
    return current && !previous;
}

bool Input::IsKeyReleased(int key) {
    bool current = IsKeyDown(key);
    auto it = s_previousKeys.find(key);
    bool previous = (it != s_previousKeys.end() && it->second);
    return !current && previous;
}

bool Input::IsMouseButtonDown(int button) {
    auto it = s_currentMouseButtons.find(button);
    return it != s_currentMouseButtons.end() && it->second;
}

bool Input::IsMouseButtonPressed(int button) {
    bool current = IsMouseButtonDown(button);
    auto it = s_previousMouseButtons.find(button);
    bool previous = (it != s_previousMouseButtons.end() && it->second);
    return current && !previous;
}

bool Input::IsMouseButtonReleased(int button) {
    bool current = IsMouseButtonDown(button);
    auto it = s_previousMouseButtons.find(button);
    bool previous = (it != s_previousMouseButtons.end() && it->second);
    return !current && previous;
}

glm::vec2 Input::GetMousePosition() {
    return s_mousePosition;
}

glm::vec2 Input::GetMouseDelta() {
    return s_mousePosition - s_previousMousePosition;
}

float Input::GetMouseScroll() {
    float scroll = s_mouseScroll;
    s_mouseScroll = 0.0f;
    return scroll;
}

void Input::SetMousePosition(double x, double y) {
    if (s_window) {
        glfwSetCursorPos(s_window, x, y);
        s_mousePosition = glm::vec2(static_cast<float>(x), static_cast<float>(y));
    }
}

void Input::SetMouseCaptured(bool captured) {
    s_mouseCaptured = captured;
    if (s_window) {
        glfwSetInputMode(s_window, GLFW_CURSOR, captured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
}

bool Input::IsMouseCaptured() {
    return s_mouseCaptured;
}

void Input::SetCursorVisible(bool visible) {
    if (s_window) {
        glfwSetInputMode(s_window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
    }
}

} // namespace triga
