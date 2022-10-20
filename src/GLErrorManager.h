#ifndef GL_ERROR_MANAGER_H
#define GL_ERROR_MANAGER_H

#include "glad/glad.h"

#define ASSERT(x) if (!(x)) exit(-1)

void GLAPIENTRY GLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam);

#endif // GL_ERROR_MANAGER_H