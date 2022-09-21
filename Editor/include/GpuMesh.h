
#pragma once

#include "FatVertex.h"

//#include <optional>
#include <vector>

namespace Oedon::Editor
{
    class GpuMesh
    {
    public:

        explicit GpuMesh(const std::vector<Vertex>& vertices);

        explicit GpuMesh(const std::vector<glm::vec3>& points);

        ~GpuMesh();

        void Bind() const;

        void Unbind();

        void Draw();

    private:
        unsigned _vao;
        unsigned _vbo;
        int _faceCount;
        bool _points;
        //std::optional<int> _ebo;
    };
}