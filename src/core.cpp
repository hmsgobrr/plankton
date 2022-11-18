#include "plankton.h"
#include "Window.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace pt {

void initWindow(int windowWidth, int windowHeight, const char* windowTitle) {
    Log::init();
    Window::getInstance().init(windowWidth, windowHeight, windowTitle);
    Renderer::getInstance().init(
        Window::getInstance().getGLFWWindow(),
        static_cast<float>(windowWidth),
        static_cast<float>(windowHeight)
    );
}

bool windowShouldClose() {
    return glfwWindowShouldClose(Window::getInstance().getGLFWWindow());
}

void exitWindow() {
    glfwSetWindowShouldClose(Window::getInstance().getGLFWWindow(), true);
}

void clearFrame(Color color) {
    Renderer::getInstance().clearFrame(color);
}

void displayWindow() {
    glfwSwapBuffers(Window::getInstance().getGLFWWindow());
}

void prepareFrame() {
    Window::getInstance().prepareFrame();
}

void shutdown() {
    Renderer::getInstance().shutdown();
    glfwTerminate();
}

float getDeltaTime() {
    return Window::getInstance().getDeltaTime();
}

void drawRect(const Rect& rect, float rotation, const Color& color) {
    Renderer::getInstance().drawRect(rect, rotation, color);
}

void drawTexture(Texture& texture, const Rect& sourceRec, const Rect& destinationRec, float rotation, const Color& tint) {
    Renderer::getInstance().drawTexture(texture, sourceRec, destinationRec, rotation, tint);
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
Key getKeyPressed() {
    return static_cast<Key>(Window::getInstance().getKeyPressed());
}

} // namespace pt
