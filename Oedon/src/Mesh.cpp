
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
        _ids{0}
    {
    }

    std::uint64_t Mesh::GetNextId()
    {
        return _ids++;
    }

    VertexId Mesh::AddVertex(const glm::vec3 &pos)
    {
        VertexId id = GetNextId();

        Vertex v{};
        v.position = pos;

        _verts[id] = v;

        return id;
    }

    FaceId Mesh::AddFace(std::initializer_list<VertexId> verts)
    {
        assert(verts.size() > 2);

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


}
