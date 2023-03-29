#include "pt/plankton.h"
#include "pt/Window.h"
#include "pt/Renderer.h"
#include "pt/Log.h"

#include <cstdlib>  // for rand(), srand(), and abs()
#include <ctime>    // for time()

namespace pt {

void initWindow(int windowWidth, int windowHeight, const char* windowTitle) { // todo srand
    Log::init();
    Window::getInstance().init(windowWidth, windowHeight, windowTitle);
    Renderer::getInstance().init(
        Window::getInstance().getGLFWWindow(),
        static_cast<float>(windowWidth),
        static_cast<float>(windowHeight)
    );
    srand((unsigned int)time(NULL));
}

bool windowShouldClose() {
    return Window::getInstance().shouldClose();
}

void closeWindow() {
    Window::getInstance().close();
}

void clearFrame(const Color& color) {
    Renderer::getInstance().clearFrame(color);
}

void display() {
    Window::getInstance().display();
}

void prepareFrame() {
    Window::getInstance().prepareFrame();
}

void setView(const Camera& camera) {
    Renderer::getInstance().setView(camera);
}

void shutdown() {
    Renderer::getInstance().shutdown();
    glfwTerminate();
}

float getDeltaTime() {
    return Window::getInstance().getDeltaTime();
}

double getTime() {
    return glfwGetTime();
}

int getRandomNumber(int min, int max) {
    // Swap min and max if min is actually bigger than max
    if (min > max) {
        int tmp = max;
        max = min;
        min = tmp;
    }

    if ((unsigned int)(max - min) > (unsigned int)RAND_MAX) {
        PT_CORE_WARN("pt::GetRandomNumber range cannot be higher than {}", RAND_MAX);
    }

    return (rand() % (abs(max - min) + 1) + min);
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

bool isMouseButtonPressed(MouseButton button) {
    return Window::getInstance().isMouseButtonPressed(static_cast<int>(button));
}
bool isMouseButtonReleased(MouseButton button) {
    return Window::getInstance().isMouseButtonReleased(static_cast<int>(button));
}
bool isMouseButtonDown(MouseButton button) {
    return Window::getInstance().isMouseButtonDown(static_cast<int>(button));
}
bool isMouseButtonUp(MouseButton button) {
    return Window::getInstance().isMouseButtonUp(static_cast<int>(button));
}
Vector2& getMousePosition() {
    return Window::getInstance().getMousePosition();
}
Vector2& getMouseWheelMovement() {
    return Window::getInstance().getMouseWheelMovement();
}

} // namespace pt
