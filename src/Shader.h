#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

#include <string>
#include <unordered_map>

class Shader {
public:
    Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

    void use();
    void unuse();

    void setUniform(const std::string& uniformName, bool value);
    void setUniform(const std::string& uniformName, int value);
    void setUniform(const std::string& uniformName, float value);
private:
    unsigned int mProgramId;
    std::unordered_map<std::string, int> mUniformLocationCache;

    int mSuccess;
    char mErrorLog[512];

    std::string loadShaderFromFile(const std::string& shaderFilePath);
    unsigned int compileShader(unsigned int shaderType, const std::string& source);
    unsigned int createShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
    int getUniformLocation(const std::string& name);
};

#endif // SHADER_H
