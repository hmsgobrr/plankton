#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <queue>

#ifndef PT_MAX_KEYBOARD_KEYS
#define PT_MAX_KEYBOARD_KEYS 512
#endif

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
    void prepareFrame();

    bool isKeyPressed(int key);
    bool isKeyReleased(int key);
    bool isKeyDown(int key);
    bool isKeyUp(int key);
    int getKeyPressed();

    GLFWwindow* getGLFWWindow() { return m_glfwWindow; }
    float getDeltaTime() { return m_deltaTime; }
    void setCurrentKeyState(int key, bool isActive);
    void enqueueKey(int key);
private:
    Window() {}

    GLFWwindow* m_glfwWindow;

    float m_lastFrameTime;
    float m_deltaTime;

    bool m_currentKeyState[PT_MAX_KEYBOARD_KEYS];
    bool m_lastKeyState[PT_MAX_KEYBOARD_KEYS];
    std::queue<int> m_pressedKeyQueue;
};

} // namespace pt

#endif
