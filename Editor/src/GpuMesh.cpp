
#include "GpuMesh.h"

#include <glbinding/gl41core/gl.h>

namespace Oedon::Editor
{
    using namespace gl;

    GpuMesh::GpuMesh(const std::vector<Vertex> &vertices)
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)__offsetof(Vertex, pos));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)__offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)__offsetof(Vertex, uv));
        glEnableVertexAttribArray(2);

        _faceCount = vertices.size();
        _points = false;
    }

    GpuMesh::GpuMesh(const std::vector<glm::vec3> &points)
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
        glEnableVertexAttribArray(0);

        _faceCount = points.size();
        _points = true;
    }

    GpuMesh::~GpuMesh()
    {
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
    }

    void GpuMesh::Bind() const
    {
        glBindVertexArray(_vao);
    }

    void GpuMesh::Unbind()
    {
        glBindVertexArray(0);
    }

    void GpuMesh::Draw()
    {
        //glDisable(GL_CULL_FACE);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDrawArrays(_points ? GL_POINTS : GL_TRIANGLES, 0, _faceCount);
    }
}