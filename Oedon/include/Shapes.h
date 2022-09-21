#pragma once

#include "FatVertex.h"
#include "Mesh.h"

#include <glm/vec3.hpp>
#include <vector>

namespace Oedon
{
    void Plane(std::vector<Vertex>& buffer, const glm::vec3& normal, float size = 1.0f);

    Mesh Cube(float size = 1.0f);

    void Sphere(std::vector<Vertex> buffer, float radius);
}
