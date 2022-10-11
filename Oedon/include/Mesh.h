#pragma once

#include <vector>
#include <unordered_map>
#include <numeric>
#include <cinttypes>

#include <glm/glm.hpp>

namespace Oedon
{
    using VertexId = std::uint64_t;
    using HalfEdgeId = std::uint64_t;
    using FaceId = std::uint64_t;
    const HalfEdgeId InvalidId = std::numeric_limits<std::uint64_t>::max();

    struct HalfEdge
    {
        explicit HalfEdge();

        HalfEdge(const HalfEdge& other);

        HalfEdgeId prev;
        HalfEdgeId next;
        HalfEdgeId twin;

        VertexId vertex;
        FaceId face;
    };

    struct Face
    {
        HalfEdgeId edge;
    };

    struct Vertex
    {
        explicit Vertex();

        Vertex(const Vertex& v);

        ~Vertex();

        glm::vec3 position;
        HalfEdgeId halfEdge;
    };

    class Mesh
    {
    public:

        explicit Mesh();

        Mesh(const Mesh& other);

        Face& GetFace(FaceId faceId);
        const Face& GetFace(FaceId faceId) const;

        Vertex& GetVertex(VertexId vertexId) ;
        const Vertex& GetVertex(VertexId vertexId) const;

        HalfEdge& GetHalfEdge(HalfEdgeId halfEdgeId);
        const HalfEdge& GetHalfEdge(HalfEdgeId halfEdgeId) const;

        VertexId AddVertex(const glm::vec3& pos, HalfEdgeId halfEdge = InvalidId);

        FaceId AddFace(const std::vector<VertexId>& verts);

        const std::vector<FaceId>& faces() const;

        const std::unordered_map<VertexId, Vertex>& verticies() const;

        void ApplyTransform(const glm::mat4& m);

    private:

        std::unordered_map<VertexId, Vertex> _verts;
        std::unordered_map<FaceId, Face> _faces;
        std::vector<FaceId> _facesV;
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
