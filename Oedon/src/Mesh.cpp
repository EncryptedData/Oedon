
#include "Mesh.h"

namespace Oedon
{


    //void ToVertecies(std::vector<Vertex>& out, const Mesh& in)
    //{
    //    assert(in.uvs.size() == in.verticies.size());
    //    assert(in.normals.size() == in.faces.size());
//
    //    const size_t faceCount = in.faces.size();
    //    for(int i = 0; i < faceCount; i++)
    //    {
    //        const Face& face = in.faces[i];
//
    //        for(unsigned int faceIndex : face.f)
    //        {
    //            Vertex v;
    //            v.pos = in.verticies[faceIndex];
    //            v.normal = in.normals[i];
    //            v.uv = in.uvs[faceIndex];
//
    //            out.emplace_back(v);
    //        }
    //    }
    //}
//
    //Face::Face(unsigned int f0, unsigned int f1, unsigned int f2)
    //{
    //    f[0] = f0;
    //    f[1] = f1;
    //    f[2] = f2;
    //}
    Mesh::Mesh() :
        _verts(),
        _faces(),
        _halfEdges(),
        _ids{1}
    {
    }

    std::uint64_t Mesh::GetNextId()
    {
        return _ids++;
    }

    VertexId Mesh::AddVertex(const glm::vec3 &pos, HalfEdgeId halfEdge)
    {
        const VertexId id = GetNextId();

        Vertex v;
        v.position = pos;
        v.halfEdge = halfEdge;

        _verts[id] = v;

        //auto pair = std::make_pair(id, v);

        //auto t = _verts.insert(pair);

        //assert(t.second);

        return id;
    }

    FaceId Mesh::AddFace(const std::vector<VertexId> &verts)
    {
        assert(verts.size() > 2);

        FaceId faceId = GetNextId();

        std::vector<HalfEdgeId> edges{};
        for(auto v : verts)
        {
            edges.emplace_back(AddHalfEdge(faceId, v));
        }

        size_t edgeIdCount = edges.size();
        for(int i = 0; i < edgeIdCount; i++)
        {
            // Get the half edge
            auto& edge = GetHalfEdge(edges[i]);

            // Determine half edge next and prev values
            int prevIndex = i - 1;
            if(prevIndex < 0)
            {
                prevIndex = edgeIdCount - 1;
            }

            int nextIndex = i + 1;
            if(nextIndex == edgeIdCount)
            {
                nextIndex = 0;
            }

            edge.next = edges[nextIndex];
            edge.prev = edges[prevIndex];

            // See if this edge has a twin
            auto& vert = GetVertex(edge.vertex);
            if(vert.halfEdge == InvalidId)
            {
                vert.halfEdge = edges[i];
            }
            else
            {
                edge.twin = vert.halfEdge;
            }
        }

        Face f{};
        f.edge = edges[0];

        _faces.insert(std::make_pair(faceId, f));
        _facesV.push_back(faceId);

        return faceId;
    }


    HalfEdgeId Mesh::AddHalfEdge(FaceId faceId, VertexId vertexId)
    {
        HalfEdgeId id = GetNextId();

        HalfEdge halfEdge{};
        halfEdge.face = faceId;
        halfEdge.vertex = vertexId;

        _halfEdges[id] = halfEdge;

        return id;
    }

    const std::vector<FaceId> &Mesh::faces() const
    {
        return _facesV;
    }

    Face &Mesh::GetFace(FaceId faceId)
    {
        auto it = _faces.find(faceId);

        assert(it != _faces.end());

        return it->second;
    }

    const Face &Mesh::GetFace(FaceId faceId) const
    {
        auto it = _faces.find(faceId);

        assert(it != _faces.end());

        return it->second;
    }

    Vertex &Mesh::GetVertex(VertexId vertexId)
    {
        auto it = _verts.find(vertexId);

        assert(it != _verts.end());

        return it->second;
    }

    const Vertex &Mesh::GetVertex(VertexId vertexId) const
    {
        auto it = _verts.find(vertexId);

        assert(it != _verts.end());

        return it->second;
    }

    HalfEdge &Mesh::GetHalfEdge(HalfEdgeId halfEdgeId)
    {
        auto it = _halfEdges.find(halfEdgeId);

        assert(it != _halfEdges.end());

        return it->second;
    }

    const HalfEdge &Mesh::GetHalfEdge(HalfEdgeId halfEdgeId) const
    {
        auto it = _halfEdges.find(halfEdgeId);

        assert(it != _halfEdges.end());

        return it->second;
    }

    Mesh::Mesh(const Mesh &other) :
        _verts(other._verts),
        _faces(other._faces),
        _facesV(other._facesV),
        _halfEdges(other._halfEdges),
        _ids{other._ids}
    {
    }

    void Mesh::ApplyTransform(const glm::mat4 &m)
    {
        for(auto& [_, vertex] : _verts)
        {
            vertex.position = glm::vec3(m * glm::vec4(vertex.position, 1.0f));
        }
    }

    const std::unordered_map<VertexId, Vertex>& Mesh::verticies() const
    {
        return _verts;
    }

    Vertex::Vertex() :
        position(0.0f),
        halfEdge(InvalidId)
    {

    }

    Vertex::Vertex(const Vertex &v) :
        position(v.position),
        halfEdge(v.halfEdge)
    {

    }

    Vertex::~Vertex()
    {
    }

    HalfEdge::HalfEdge(const HalfEdge& other) :
        prev(other.prev),
        next(other.next),
        twin(other.twin),
        vertex(other.vertex),
        face(other.face)
    {

    }

    HalfEdge::HalfEdge() :
        prev(InvalidId),
        next(InvalidId),
        twin(InvalidId),
        vertex(InvalidId),
        face(InvalidId)
    {
    }
}
