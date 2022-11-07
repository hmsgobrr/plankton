#include "Window.h"

#include "Log.h"

namespace pt {

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key < 0) return; // In case key that generates -1 or lower like MacOS fn key gets pressed

    if (action == GLFW_RELEASE) {
        Window::getInstance().setCurrentKeyState(key, false);
        return;
    }
    
    Window::getInstance().setCurrentKeyState(key, true);
    Window::getInstance().enqueueKey(key);
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

    glfwPollEvents();
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

void Window::setCurrentKeyState(int key, bool isActive) {
    if (key >= PT_MAX_KEYBOARD_KEYS) return;
    m_currentKeyState[key] = isActive;
}

void Window::enqueueKey(int key) {
    m_pressedKeyQueue[m_pressedKeyCount] = key;
    m_pressedKeyCount++;
}

} // namespace pt
