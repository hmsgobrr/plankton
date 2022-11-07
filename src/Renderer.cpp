#include "Renderer.h"

#include "Log.h"

#include "GLErrorManager.h"

namespace pt {

void Renderer::init(GLFWwindow* contextWindow) {
    glfwMakeContextCurrent(contextWindow);

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

}
