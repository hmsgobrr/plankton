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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_shader.create(ASSETS_PATH"shaders/shape.vert", ASSETS_PATH"shaders/shape.frag");
    m_shader.use();
    glm::mat4 projection = glm::ortho(0.0f, frameWidth, frameHeight, 0.0f, -1.0f, 1.0f);
    m_shader.setUniform("projection", projection);
    m_shader.setUniform("view", glm::mat4(1.0f));

    // Init render data
    float vertices[] {
        // vertex   texcoord 
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    unsigned int indicies[] = {
        0, 1, 2,
        1, 2, 3
    };

    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &m_quadVBO);
    glGenBuffers(1, &m_quadIB);

    glBindVertexArray(m_quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quadIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::shutdown() {
    m_shader.destroy();
    glDeleteVertexArrays(1, &m_quadVAO);
    glDeleteBuffers(1, &m_quadVBO);
    glDeleteBuffers(1, &m_quadIB);
}

void Renderer::clearFrame(const Color& color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::setView(const Camera& camera) {
    glm::mat4 view(1.0f);

    // position back from zoom & rotate origin and alse translate by the inverse of camera pos
    view = glm::translate(view, glm::vec3(
        camera.zoomRotationOrigin.x - camera.position.x,
        camera.zoomRotationOrigin.y - camera.position.y,
        0.0f
    ));

    view = glm::rotate(view, glm::radians(camera.rotation), glm::vec3(0.0f, 0.0f ,1.0f)); // rotate
    view = glm::scale(view, glm::vec3(camera.zoom, camera.zoom, 1.0f)); // zoom

    view = glm::translate(view, glm::vec3(camera.zoomRotationOrigin.x, camera.zoomRotationOrigin.y, 0.0f)); // move to origin for zooming & rotating

    m_shader.setUniform("view", view);
}

void Renderer::drawRect(const Rect& rect, float rotation, const Color& color) {
    m_shader.use();

    m_shader.setUniform("useTex", false);
    m_shader.setUniform("shapeColor", color.r, color.g, color.b, color.a);

    drawQuad(rect, rotation);
}

void Renderer::drawTexture(Texture& texture, const Rect& sourceRec, const Rect& destinationRec, float rotation, const Color& tint) {
    m_shader.use();

    glm::mat4 texCoordsTransform(1.0f);

    texCoordsTransform = glm::translate(texCoordsTransform, glm::vec3(sourceRec.x, sourceRec.y, 0.0f));
    texCoordsTransform = glm::scale(texCoordsTransform, glm::vec3(sourceRec.w, sourceRec.h, 1.0f));

    m_shader.setUniform("useTex", true);
    m_shader.setUniform("texCoordsTransform", texCoordsTransform);
    m_shader.setUniform("shapeColor", tint.r, tint.g, tint.b, tint.a);

    texture.use();
    drawQuad(destinationRec, rotation);
}

void Renderer::drawQuad(const Rect& rect, float rotation) {
    glm::mat4 model(1.0f);

    // Move to position
    model = glm::translate(model, glm::vec3(rect.x, rect.y, 0.0f));

    if (rotation != 0.0f) {
        // Rotate
        model = glm::translate(model, glm::vec3(0.5f * rect.w, 0.5f * rect.h, 0.0f)); // move origin of rotation to center of quad
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
        model = glm::translate(model, glm::vec3(-0.5f * rect.w, -0.5f * rect.h, 0.0f)); // move origin back
    }

    // Scale
    model = glm::scale(model, glm::vec3(rect.w, rect.h, 1.0f));
    m_shader.setUniform("model", model);

    glBindVertexArray(m_quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

}
