#include "triga/core/Window.h"
#include "triga/core/Logger.h"
#include <GLFW/glfw3.h>

namespace triga {

Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title) {

    if (!glfwInit()) {
        TRIGA_LOG_ERROR("Failed to initialize GLFW");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        TRIGA_LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(m_window, this);

    glfwSetFramebufferSizeCallback(m_window, glfwResizeCallback);
    glfwSetKeyCallback(m_window, glfwKeyCallback);
    glfwSetMouseButtonCallback(m_window, glfwMouseButtonCallback);
    glfwSetCursorPosCallback(m_window, glfwMousePosCallback);

    TRIGA_LOG_INFO("Window created: {}x{} - {}", width, height, title);
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool Window::shouldClose() const {
    return m_window && glfwWindowShouldClose(m_window);
}

void Window::swapBuffers() {
    if (m_window) {
        glfwSwapBuffers(m_window);
    }
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::close() {
    if (m_window) {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }
}

bool Window::isKeyPressed(int key) const {
    return m_window && glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool Window::isMouseButtonPressed(int button) const {
    return m_window && glfwGetMouseButton(m_window, button) == GLFW_PRESS;
}

void Window::getMousePosition(double& x, double& y) const {
    if (m_window) {
        glfwGetCursorPos(m_window, &x, &y);
    }
}

void Window::setVSync(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
}

void Window::maximize() {
    if (m_window) {
        glfwMaximizeWindow(m_window);
    }
}

void Window::minimize() {
    if (m_window) {
        glfwIconifyWindow(m_window);
    }
}

void Window::restore() {
    if (m_window) {
        glfwRestoreWindow(m_window);
    }
}

double Window::getTime() const {
    return glfwGetTime();
}

void Window::glfwResizeCallback(GLFWwindow* window, int width, int height) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win && win->m_resizeCallback) {
        win->m_resizeCallback(width, height);
    }
}

void Window::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win && win->m_keyCallback) {
        win->m_keyCallback(key, scancode, action, mods);
    }
}

void Window::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win && win->m_mouseButtonCallback) {
        win->m_mouseButtonCallback(button, action, mods);
    }
}

void Window::glfwMousePosCallback(GLFWwindow* window, double xpos, double ypos) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win && win->m_mousePosCallback) {
        win->m_mousePosCallback(xpos, ypos);
    }
}

} // namespace triga
