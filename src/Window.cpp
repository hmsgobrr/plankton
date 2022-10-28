#include "Window.h"
#include "Log.h"

#include "GLErrorManager.h"

namespace pt {

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

} // namespace pt
