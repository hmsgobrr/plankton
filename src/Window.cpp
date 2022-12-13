#include "Window.h"

#include "Log.h"

namespace pt {

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key < 0) return; // In case key that generates -1 or lower like MacOS fn key gets pressed

    if (action == GLFW_RELEASE) {
        Window::getInstance().setCurrentKeyState(key, false);
        return;
    }
    
    Window::getInstance().setCurrentKeyState(key, true);
    Window::getInstance().enqueueKey(key);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button < 0) return;

    if (action == GLFW_RELEASE) {
        Window::getInstance().setCurrentMouseButtonState(button, false);
        return;
    }

    Window::getInstance().setCurrentMouseButtonState(button, true);
}

static void mouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    Window::getInstance().setMouseCursorPos((float)xpos, (float)ypos);
}

static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Window::getInstance().setMouseWheelMovement(xoffset, yoffset);
}

void Window::init(int windowWidth, int windowHeight, const char* windowTitle) {
    // Init GLFW
    if (!glfwInit()) {
        PT_CORE_CRITICAL("GLFW init failed");
        return;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    m_glfwWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
    if (!m_glfwWindow) {
        PT_CORE_CRITICAL("Window creation failed");
        return;
    }
    glfwSetWindowAttrib(m_glfwWindow, GLFW_RESIZABLE, GLFW_FALSE);
    glfwSetKeyCallback(m_glfwWindow, keyCallback);
    glfwSetMouseButtonCallback(m_glfwWindow, mouseButtonCallback);
    glfwSetCursorPosCallback(m_glfwWindow, mouseCursorPosCallback);
    glfwSetScrollCallback(m_glfwWindow, scrollCallback);
}

void Window::prepareFrame() {
    // update delta time
    float currentTime = glfwGetTime();
    m_deltaTime = currentTime - m_lastFrameTime;
    m_lastFrameTime = currentTime;

    // save last key states before updating them
    for (int i = 0; i < PT_MAX_KEYBOARD_KEYS; i++) {
        m_lastKeyState[i] = m_currentKeyState[i];
    }

    // reset key queue
    for (int i = 0; i < m_pressedKeyCount; i++) {
        m_pressedKeyQueue[i] = 0;
    }
    m_pressedKeyCount = 0;

    // save last mouse button state
    for (int i = 0; i < PT_MAX_MOUSE_BUTTON_COUNT; i++) {
        m_lastMouseButtonState[i] = m_currentMouseButtonState[i];
    }

    // reset mouse wheel movement value
    m_mouseWheelMovement.x = 0.0f;
    m_mouseWheelMovement.y = 0.0f;

    glfwPollEvents();
}

void Window::close() {
    glfwSetWindowShouldClose(m_glfwWindow, true);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(m_glfwWindow);
}

void Window::display() {
    glfwSwapBuffers(m_glfwWindow);
}

bool Window::isKeyPressed(int key) {
    return !m_lastKeyState[key] && m_currentKeyState[key];
}
bool Window::isKeyReleased(int key) {
    return m_lastKeyState[key] && !m_currentKeyState[key];
}
bool Window::isKeyDown(int key) {
    return m_currentKeyState[key];
}
bool Window::isKeyUp(int key) {
    return !m_currentKeyState[key];
}
int Window::getKeyPressed() {
    if (m_pressedKeyCount < 1) return 0;
    
    int key = m_pressedKeyQueue[0];
    // shift key queue forward
    for (int i = 0; i < m_pressedKeyCount - 1; i++) {
        m_pressedKeyQueue[i] = m_pressedKeyQueue[i + 1];
    }
    m_pressedKeyQueue[m_pressedKeyCount] = 0;
    m_pressedKeyCount--;

    return key;
}

bool Window::isMouseButtonPressed(int button) {
    return !m_lastMouseButtonState[button] && m_currentMouseButtonState[button];
}
bool Window::isMouseButtonReleased(int button) {
    return m_lastMouseButtonState[button] && !m_currentMouseButtonState[button];
}
bool Window::isMouseButtonDown(int button) {
    return m_currentMouseButtonState[button];
}
bool Window::isMouseButtonUp(int button) {
    return !m_currentMouseButtonState[button];
}
Vector2& Window::getMousePosition() {
    return m_mouseCursorPos;
}
Vector2& Window::getMouseWheelMovement() {
    return m_mouseWheelMovement;
}

void Window::setCurrentKeyState(int key, bool isActive) {
    if (key >= PT_MAX_KEYBOARD_KEYS) return;
    m_currentKeyState[key] = isActive;
}

void Window::enqueueKey(int key) {
    m_pressedKeyQueue[m_pressedKeyCount] = key;
    m_pressedKeyCount++;
}

void Window::setCurrentMouseButtonState(int button, bool isActive) {
    if (button >= PT_MAX_MOUSE_BUTTON_COUNT) return;
    m_currentMouseButtonState[button] = isActive;
}

void Window::setMouseCursorPos(float mouseX, float mouseY) {
    m_mouseCursorPos.x = mouseX;
    m_mouseCursorPos.y = mouseY;
}

void Window::setMouseWheelMovement(float x, float y) {
    m_mouseWheelMovement.x = x;
    m_mouseWheelMovement.y = y;
}

} // namespace pt
