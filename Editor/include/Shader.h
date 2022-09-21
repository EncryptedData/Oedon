#pragma once

#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>
#include <glm/glm.hpp>

namespace Oedon::Editor
{
    enum class ShaderType
    {
        Vertex,
        Fragment,
        Compute
    };

    class Shader
    {
    public:

        bool Compile(std::string_view shaderSource, ShaderType shaderType);

        bool Link();

        void Bind();

        void Unbind();

        void Set(std::string_view uniformName, const glm::vec2& a);
        void Set(std::string_view uniformName, const glm::vec3& a);
        void Set(std::string_view uniformName, const glm::vec4& a);
        void Set(std::string_view uniformName, const glm::mat3& a);
        void Set(std::string_view uniformName, const glm::mat4& a);

    private:
        unsigned _programId;
        std::vector<unsigned> _compiled;
        std::unordered_map<std::string, int> _uniformLocations;


        int GetLocation(std::string_view uniformName);
    };
}
