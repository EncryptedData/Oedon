#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "Mesh.h"

namespace Oedon
{
    struct FatVertex
    {
        explicit FatVertex(const glm::vec3& p, const glm::vec3& n, const glm::vec2& tex);

        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    void ToFatVerticies(std::vector<FatVertex>& out, const Mesh& in);
}
