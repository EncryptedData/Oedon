#pragma once

#include "FatVertex.h"
#include "Mesh.h"

#include <glm/vec3.hpp>
#include <vector>

namespace Oedon
{
    void Plane(std::vector<Vertex>& buffer, const glm::vec3& normal, float size = 1.0f);

    Mesh Cube(float size = 1.0f);

    Mesh Sphere(std::uint64_t hcount, std::uint64_t vcount, float diameter = 1.0f);
}
