#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>

namespace pt {
class Window {
public:
    // Singleton stuff
    Window(Window const&) = delete;
    void operator=(Window const&) = delete;
    static Window& getInstance() {
        static Window instance;
        return instance;
    }

    void init(int windowWidth, int windowHeight, const char* windowTitle);

    GLFWwindow* getGLFWWindow() { return m_glfwWindow; }
private:
    Window() {}

    GLFWwindow* m_glfwWindow;
};
} // namespace pt

#endif
