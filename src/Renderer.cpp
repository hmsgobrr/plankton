#include "Renderer.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include <cstdlib> // for exit()

#include "Log.h"

#ifndef ASSETS_PATH
#define ASSETS_PATH "../assets/"
#endif

namespace pt {

static void GLAPIENTRY GLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam) {
    char* _source;
    char* _type;

    switch (source) {
    case GL_DEBUG_SOURCE_API:
        _source = (char*)"API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = (char*)"WINDOW SYSTEM";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = (char*)"SHADER COMPILER";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = (char*)"THIRD PARTY";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        _source = (char*)"APPLICATION";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        _source = (char*)"UNKNOWN";
        break;
    default:
        _source = (char*)"UNKNOWN";
        break;
    }

    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        _type = (char*)"ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = (char*)"DEPRECATED BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = (char*)"UDEFINED BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        _type = (char*)"PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = (char*)"PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        _type = (char*)"OTHER";
        break;
    case GL_DEBUG_TYPE_MARKER:
        _type = (char*)"MARKER";
        break;
    default:
        _type = (char*)"UNKNOWN";
        break;
    }

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        PT_CORE_CRITICAL("OpengGL Critical Error ({}): {} from {}. {}", id, _type, _source, message);
        exit(-1);
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        PT_CORE_ERROR("OpengGL Error ({}): {} from {}. {}", id, _type, _source, message);
        break;
    case GL_DEBUG_SEVERITY_LOW:
        PT_CORE_WARN("OpengGL Minor Error ({}): {} from {}. {}", id, _type, _source, message);
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        PT_CORE_INFO("OpengGL Info ({}): {} from {}. {}", id, _type, _source, message);
        break;
    default:
        PT_CORE_INFO("OpengGL Unknown Notification ({}): {} from {}. {}", id, _type, _source, message);
        break;
    }
}

void Renderer::init(GLFWwindow* contextWindow, float p_frameWidth, float p_frameHeight) {
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
    m_frameWidth = p_frameWidth;
    m_frameHeight = p_frameHeight;
    glm::mat4 projection = glm::ortho(0.0f, m_frameWidth, m_frameHeight, 0.0f, -1.0f, 1.0f);
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

    Vector2 zoomRotationOrigin = { m_frameWidth/2.0f, m_frameHeight/2.0f };

    // position back from zoom & rotate origin
    view = glm::translate(view, glm::vec3(zoomRotationOrigin.x, zoomRotationOrigin.y, 0.0f));

    view = glm::rotate(view, glm::radians(-camera.rotation), glm::vec3(0.0f, 0.0f ,1.0f)); // rotate
    view = glm::scale(view, glm::vec3(camera.zoom, camera.zoom, 1.0f)); // zoom

    // move to origin for zooming & rotating
    view = glm::translate(view, glm::vec3(-zoomRotationOrigin.x, -zoomRotationOrigin.y, 0.0f));

    // move object to opposite direction of the camera's movement
    view = glm::translate(view, glm::vec3(-camera.position.x, -camera.position.y, 0.0f));

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
