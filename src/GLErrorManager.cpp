#include "GLErrorManager.h"
#include "Log.h"

#include <iostream>

void GLAPIENTRY GLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
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
        ASSERT(false);
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
