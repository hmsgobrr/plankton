#include "Window.h"
#include "Log.h"

#include "GLErrorManager.h"

namespace pt {

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key < 0) return; // In case of key that generates -1 or lower like MacOS fn key gets pressed

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

    // Create OpenGL context window
    m_glfwWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
    if (!m_glfwWindow) {
        PT_CORE_CRITICAL("Window creation failed");
        return;
    }
    glfwMakeContextCurrent(m_glfwWindow);
    glfwSetWindowAttrib(m_glfwWindow, GLFW_RESIZABLE, GLFW_FALSE);

    // Set callback for keyboard inputs
    glfwSetKeyCallback(m_glfwWindow, keyCallback);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        PT_CORE_CRITICAL("GLAD init failed");
        return;
    }

    glDebugMessageCallback(GLLogMessage, nullptr);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void Window::pollEvents() {
    // save last key states before updating them
    for (int i = 0; i < PT_MAX_KEYBOARD_KEYS; i++) {
        m_lastKeyState[i] = m_currentKeyState[i];
    }

    // reset key queue
    for (int i = 0; i < m_pressedKeyQueue.size(); i++) {
        m_pressedKeyQueue.pop();
    }

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
    if (m_pressedKeyQueue.empty()) return 0;
    
    int key = m_pressedKeyQueue.front();
    m_pressedKeyQueue.pop();

    return key;
}

void Window::setCurrentKeyState(int key, bool isActive) {
    if (key >= PT_MAX_KEYBOARD_KEYS) return;
    m_currentKeyState[key] = isActive;
}

void Window::enqueueKey(int key) {
    m_pressedKeyQueue.push(key);
}

} // namespace pt
