#include "pt/Shader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include "pt/Log.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace pt {

void Shader::create(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
    mProgramId = createShader(loadShaderFromFile(vertexShaderFilePath), loadShaderFromFile(fragmentShaderFilePath));
}

void Shader::destroy() {
    glDeleteProgram(mProgramId);
}

std::string Shader::loadShaderFromFile(const std::string& shaderFilePath) {
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(shaderFilePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        return shaderStream.str();
    } catch (std::ifstream::failure e) {
        PT_CORE_CRITICAL("Failed to read shader file: {}.", shaderFilePath);
        return nullptr;
    }
}

unsigned int Shader::compileShader(unsigned int shaderType, const std::string& source) {
    unsigned int shader = glCreateShader(shaderType);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &mSuccess);
    if (!mSuccess) {
        glGetShaderInfoLog(shader, 512, NULL, mErrorLog);
        std::cout << "ERR! " << (shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
            << " Shader compilation failed.\n" << mErrorLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

unsigned int Shader::createShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &mSuccess);
    if (!mSuccess) {
        glGetProgramInfoLog(program, 512, NULL, mErrorLog);
        std::cout << "ERR! Shader Program linking failed.\n" << mErrorLog << std::endl;
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::use() {
    glUseProgram(mProgramId);
}

void Shader::unuse() {
    glUseProgram(0);
}

void Shader::setUniform(const std::string& uniformName, bool value) {
    glUniform1i(getUniformLocation(uniformName), (int)value);
}
void Shader::setUniform(const std::string& uniformName, int value) {
    glUniform1i(getUniformLocation(uniformName), value);
}
void Shader::setUniform(const std::string& uniformName, float value) {
    glUniform1f(getUniformLocation(uniformName), value);
}
void Shader::setUniform(const std::string& uniformName, const glm::mat4& matrix4) {
    glUniformMatrix4fv(getUniformLocation(uniformName), 1, false, glm::value_ptr(matrix4));
}
void Shader::setUniform(const std::string& uniformName, float x, float y, float z, float w) {
    glUniform4f(getUniformLocation(uniformName), x, y, z, w);
}

int Shader::getUniformLocation(const std::string& uniformName) {
    if (mUniformLocationCache.find(uniformName) != mUniformLocationCache.end())
        return mUniformLocationCache[uniformName];

    int location = glGetUniformLocation(mProgramId, uniformName.c_str());
    if (location == -1) {
        std::cout << "WARN! Failed to find uniform " << uniformName << "." << std::endl;
    }
    mUniformLocationCache[uniformName] = location;

    return location;
}

}
