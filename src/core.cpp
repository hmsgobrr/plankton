#include "plankton.h"
#include "Window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace pt {

void initWindow(int windowWidth, int windowHeight, const char* windowTitle) {
    Log::init();
    Window::getInstance().init(windowWidth, windowHeight, windowTitle);
}

bool windowShouldClose() {
    return glfwWindowShouldClose(Window::getInstance().getGLFWWindow());
}

void exitWindow() {
    glfwSetWindowShouldClose(Window::getInstance().getGLFWWindow(), false);
}

void clearWindow(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void displayWindow() {
    glfwSwapBuffers(Window::getInstance().getGLFWWindow());
    glfwPollEvents();
}

void shutdown() {
    glfwTerminate();
}

} // namespace pt
