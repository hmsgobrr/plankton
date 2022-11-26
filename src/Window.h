#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#ifndef PT_MAX_KEYBOARD_KEYS
#define PT_MAX_KEYBOARD_KEYS 512
#endif

#ifndef PT_MAX_PRESSED_KEY_QUEUE
#define PT_MAX_PRESSED_KEY_QUEUE 16
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
    void close();
    bool shouldClose();
    void display();

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
    Window():
        m_glfwWindow(0),
        m_lastFrameTime(0.0f),
        m_deltaTime(0.0f),
        m_currentKeyState(),
        m_lastKeyState(),
        m_pressedKeyQueue(),
        m_pressedKeyCount(0) {}

    GLFWwindow* m_glfwWindow;

    float m_lastFrameTime;
    float m_deltaTime;

    bool m_currentKeyState[PT_MAX_KEYBOARD_KEYS];
    bool m_lastKeyState[PT_MAX_KEYBOARD_KEYS];

    int m_pressedKeyQueue[PT_MAX_PRESSED_KEY_QUEUE];
    int m_pressedKeyCount;
};

} // namespace pt

#endif
