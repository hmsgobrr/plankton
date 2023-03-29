#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "pt/plankton.h"

#ifndef PT_MAX_KEYBOARD_KEYS
#define PT_MAX_KEYBOARD_KEYS 512
#endif

#ifndef PT_MAX_PRESSED_KEY_QUEUE
#define PT_MAX_PRESSED_KEY_QUEUE 16
#endif

#ifndef PT_MAX_MOUSE_BUTTON_COUNT
#define PT_MAX_MOUSE_BUTTON_COUNT 3
#endif

namespace pt {

// Wrapper class for GLFW functions, meant to be used only from main api (plankton.h) not directly.
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
 
    bool isMouseButtonPressed(int button);
    bool isMouseButtonReleased(int button);
    bool isMouseButtonDown(int button);
    bool isMouseButtonUp(int button);
    Vector2& getMousePosition();
    Vector2& getMouseWheelMovement();

    GLFWwindow* getGLFWWindow() { return m_glfwWindow; }

    float getDeltaTime() { return m_deltaTime; }

    void setCurrentKeyState(int key, bool isActive);
    void enqueueKey(int key);
    void setCurrentMouseButtonState(int button, bool isActive);
    void setMouseCursorPos(float mouseX, float mouseY);
    void setMouseWheelMovement(float x, float y);
private:
    Window():
        m_glfwWindow(0),
        m_lastFrameTime(0.0f),
        m_deltaTime(0.0f),
        m_currentKeyState(),
        m_lastKeyState(),
        m_pressedKeyQueue(),
        m_pressedKeyCount(0),
        m_currentMouseButtonState(),
        m_lastMouseButtonState(),
        m_mouseCursorPos({ 0.0f, 0.0f }),
        m_mouseWheelMovement({ 0.0f, 0.0f }) {}

    GLFWwindow* m_glfwWindow;

    float m_lastFrameTime;
    float m_deltaTime;

    bool m_currentKeyState[PT_MAX_KEYBOARD_KEYS];
    bool m_lastKeyState[PT_MAX_KEYBOARD_KEYS];

    int m_pressedKeyQueue[PT_MAX_PRESSED_KEY_QUEUE];
    int m_pressedKeyCount;

    bool m_currentMouseButtonState[PT_MAX_MOUSE_BUTTON_COUNT];
    bool m_lastMouseButtonState[PT_MAX_MOUSE_BUTTON_COUNT];
    Vector2 m_mouseCursorPos;
    Vector2 m_mouseWheelMovement;
};

} // namespace pt

#endif
