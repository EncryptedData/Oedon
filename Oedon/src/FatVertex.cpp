//
// Created by rjohnson on 9/21/22.
//

#include "FatVertex.h"

namespace Oedon
{
    void ToFatVerticies(std::vector<FatVertex>& out, const Mesh& in)
    {
        for(const auto faceId : in.faces())
        {
            const auto& face = in.GetFace(faceId);

            HalfEdgeId startId = face.edge;
            const HalfEdge& start = in.GetHalfEdge(startId);
            HalfEdgeId currentId = start.next;

            while(true)
            {
                const HalfEdge& current = in.GetHalfEdge(currentId);
                HalfEdgeId nextId = current.next;

                if(nextId == startId)
                {
                    break;
                }

                const HalfEdge& next = in.GetHalfEdge(nextId);

                const Vertex& A = in.GetVertex(start.vertex);
                const Vertex& B = in.GetVertex(current.vertex);
                const Vertex& C = in.GetVertex(next.vertex);

                glm::vec3 normal = glm::normalize(glm::cross(B.position - A.position, C.position - A.position));
                out.emplace_back(FatVertex(A.position, normal, glm::vec2(0.0f)));
                out.emplace_back(FatVertex(B.position, normal, glm::vec2(0.0f)));
                out.emplace_back(FatVertex(C.position, normal, glm::vec2(0.0f)));

                currentId = nextId;
            }
        }
    }

    FatVertex::FatVertex(const glm::vec3 &p, const glm::vec3 &n, const glm::vec2 &tex) :
        pos(p),
        normal(n),
        uv(tex)
    {
    }
}
