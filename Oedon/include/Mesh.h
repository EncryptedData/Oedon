#pragma once

#include "FatVertex.h"

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Oedon
{
    using VertexId = std::uint64_t;
    using HalfEdgeId = std::uint64_t;
    using FaceId = std::uint64_t;

    struct HalfEdge
    {
        HalfEdgeId prev;
        HalfEdgeId next;
        //HalfEdgeId twin;

        VertexId vertex;
        FaceId face;
    };

    struct Face
    {
        HalfEdgeId edge;
    };

    struct Vertex
    {
        glm::vec3 position;
    };

    class Mesh
    {
    public:

        explicit Mesh();

        Face& GetFace(FaceId faceId);

        Vertex& GetVertex(VertexId vertexId);

        HalfEdge& GetHalfEdge(HalfEdgeId halfEdgeId);

        VertexId AddVertex(const glm::vec3& pos);



        FaceId AddFace(std::initializer_list<VertexId> verts);

    private:

        std::unordered_map<VertexId, Vertex> _verts;
        std::unordered_map<FaceId, Face> _faces;
        std::unordered_map<HalfEdgeId, HalfEdge> _halfEdges;
        std::uint64_t _ids;

        std::uint64_t GetNextId();

        HalfEdgeId AddHalfEdge(FaceId faceId, VertexId vertexId);
    };

    //struct Face
    //{
    //    explicit Face(unsigned f0, unsigned f1, unsigned f2);
//
    //    unsigned f[3];
    //};
//
    //struct Mesh
    //{
    //    std::vector<glm::vec3> verticies;
    //    std::vector<glm::vec3> normals;
    //    std::vector<glm::vec2> uvs;
    //    std::vector<Face> faces;
    //};

    //void ToVertecies(std::vector<Vertex>& out, const Mesh& in);

    //void FromVertecies(Mesh& out, const std::vector<Vertex>& in);

}
