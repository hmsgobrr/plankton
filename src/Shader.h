#ifndef SHADER_H
#define SHADER_H

#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

namespace pt {

class Shader {
public:
    void create(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
    void destroy();

    void use();
    void unuse();

    void setUniform(const std::string& uniformName, bool value);
    void setUniform(const std::string& uniformName, int value);
    void setUniform(const std::string& uniformName, float value);
    void setUniform(const std::string& uniformName, float x, float y, float z, float w);
    void setUniform(const std::string& uniformName, const glm::mat4& matrix4);
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

}

#endif // SHADER_H
