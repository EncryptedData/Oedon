
#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glbinding/gl46core/gl.h>

#include <iostream>

namespace Oedon::Editor
{
    using namespace gl;

    bool Shader::Compile(std::string_view shaderSource, ShaderType shaderType)
    {
        GLenum type;

        switch (shaderType)
        {
            case ShaderType::Fragment:
                type = GL_FRAGMENT_SHADER;
                break;
            case ShaderType::Vertex:
                type = GL_VERTEX_SHADER;
                break;
            case ShaderType::Compute:
                [[fallthrough]];
            default:
                type = GL_COMPUTE_SHADER;
              break;
        }

        const char* shim[] = {
                shaderSource.data(),
        };

        unsigned shader = glCreateShader(type);
        glShaderSource(shader, 1, shim, nullptr);
        glCompileShader(shader);

        _compiled.push_back(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            char log[512];
            glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
            std::cout << "Shader Compile failed: " << log << std::endl;
        }

        assert(success);

        return !!success;
    }

    bool Shader::Link()
    {
        _programId = glCreateProgram();

        for(const auto& shader : _compiled)
        {
            glAttachShader(_programId, shader);
        }

        glLinkProgram(_programId);

        int success;
        glGetProgramiv(_programId, GL_LINK_STATUS, &success);

        if(!success)
        {
            char log[512];
            glGetProgramInfoLog(_programId, sizeof(log), nullptr, log);
            std::cout << "Shader Link failed: " << log << std::endl;
        }

        assert(success);

        return !!success;
    }

    void Shader::Bind()
    {
        glUseProgram(_programId);
    }

    void Shader::Unbind()
    {
        const unsigned nullProgramId = 0;
        glUseProgram(nullProgramId);
    }

    int Shader::GetLocation(std::string_view uniformName)
    {
        auto it = _uniformLocations.find(uniformName.data());

        if(it != _uniformLocations.end())
        {
            return it->second;
        }

        int location = glGetUniformLocation(_programId, uniformName.data());

        _uniformLocations[uniformName.data()] = location;

        return location;
    }

    void Shader::Set(std::string_view uniformName, const glm::vec2 &a)
    {
        int loc = GetLocation(uniformName);

        glUniform2fv(loc, 1, glm::value_ptr(a));
    }

    void Shader::Set(std::string_view uniformName, const glm::vec3 &a)
    {
        int loc = GetLocation(uniformName);

        glUniform3fv(loc, 1, glm::value_ptr(a));
    }

    void Shader::Set(std::string_view uniformName, const glm::vec4 &a)
    {
        int loc = GetLocation(uniformName);

        glUniform4fv(loc, 1, glm::value_ptr(a));
    }

    void Shader::Set(std::string_view uniformName, const glm::mat3 &a)
    {
        int loc = GetLocation(uniformName);

        glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(a));
    }

    void Shader::Set(std::string_view uniformName, const glm::mat4 &a)
    {
        int loc = GetLocation(uniformName);

        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(a));
    }

}
