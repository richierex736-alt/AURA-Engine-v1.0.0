#pragma once

#include <string>
#include <functional>
#include <GLFW/glfw3.h>

namespace triga {

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    void close();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    float getAspectRatio() const { return static_cast<float>(m_width) / static_cast<float>(m_height); }
    GLFWwindow* getGLFWWindow() const { return m_window; }

    void setResizeCallback(std::function<void(int, int)> callback) { m_resizeCallback = callback; }
    void setKeyCallback(std::function<void(int, int, int, int)> callback) { m_keyCallback = callback; }
    void setMouseButtonCallback(std::function<void(int, int, int)> callback) { m_mouseButtonCallback = callback; }
    void setMousePosCallback(std::function<void(double, double)> callback) { m_mousePosCallback = callback; }

    bool isKeyPressed(int key) const;
    bool isMouseButtonPressed(int button) const;
    void getMousePosition(double& x, double& y) const;

    void setVSync(bool enabled);
    void maximize();
    void minimize();
    void restore();

    double getTime() const;

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;

    std::function<void(int, int)> m_resizeCallback;
    std::function<void(int, int, int, int)> m_keyCallback;
    std::function<void(int, int, int)> m_mouseButtonCallback;
    std::function<void(double, double)> m_mousePosCallback;

    static void glfwResizeCallback(GLFWwindow* window, int width, int height);
    static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void glfwMousePosCallback(GLFWwindow* window, double xpos, double ypos);
};

} // namespace triga
