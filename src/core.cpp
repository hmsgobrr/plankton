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
    glfwSetWindowShouldClose(Window::getInstance().getGLFWWindow(), true);
}

void clearWindow(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void displayWindow() {
    glfwSwapBuffers(Window::getInstance().getGLFWWindow());
    Window::getInstance().pollEvents();
}

void shutdown() {
    glfwTerminate();
}

bool isKeyPressed(Key key) {
    return Window::getInstance().isKeyPressed(static_cast<int>(key));
}
bool isKeyReleased(Key key) {
    return Window::getInstance().isKeyReleased(static_cast<int>(key));
}
bool isKeyDown(Key key) {
    return Window::getInstance().isKeyDown(static_cast<int>(key));
}
bool isKeyUp(Key key) {
    return Window::getInstance().isKeyUp(static_cast<int>(key));
}

} // namespace pt
