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

    glViewport(0, 0, frameWidth, frameHeight);

    m_shapeShader.create(ASSETS_PATH"shaders/shape.vert", ASSETS_PATH"shaders/shape.frag");
    m_shapeShader.use();
    glm::mat4 projection = glm::ortho(0.0f, frameWidth, frameHeight, 0.0f, -1.0f, 1.0f);
    m_shapeShader.setUniform("projection", projection);

    // Init render data
    float vertices[] {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &m_quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_quadVAO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::shutdown() {
    m_shapeShader.destroy();
    glDeleteVertexArrays(1, &m_quadVAO);
    glDeleteBuffers(1, &m_quadVBO);
}

void Renderer::clearFrame(Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawRect(Rect rect, Color color) {
    m_shapeShader.use();

    glm::mat4 model(1.0f);

    // Move to position
    model = glm::translate(model, glm::vec3(rect.x, rect.y, 0.0f));

    // Rotate
    //model = glm::translate(model, glm::vec3(0.5f * rect.x, 0.5f * rect.y, 0.0f)); // move origin of rotation to center of quad
    //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    //model = glm::translate(model, glm::vec3(-0.5f * rect.x, -0.5f * rect.y, 0.0f)); // move origin back

    // Scale
    model = glm::scale(model, glm::vec3(rect.w, rect.h, 1.0f));
    m_shapeShader.setUniform("model", model);

    m_shapeShader.setUniform("shapeColor", color.r, color.g, color.b, color.a);

    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

}
