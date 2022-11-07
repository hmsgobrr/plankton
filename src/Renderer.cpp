#include "Renderer.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include "Log.h"
#include "GLErrorManager.h"

#ifndef ASSETS_PATH
#define ASSETS_PATH "../assets/"
#endif

namespace pt {

void Renderer::init(GLFWwindow* contextWindow, float frameWidth, float frameHeight) {
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

    m_shapeShader.create(ASSETS_PATH"shaders/shape.vert", ASSETS_PATH"shaders/shape.frag");
    glm::mat4 projection = glm::ortho(0.0f, frameWidth, frameHeight, 0.0f, -1.0f, 1.0f);
    m_shapeShader.setUniform("projection", projection);

    // Init render data
    unsigned int vbo;
    float vertices[] {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_quadVAO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::shutdown() {
    m_shapeShader.destroy();
}

void Renderer::clearFrame(Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

}
