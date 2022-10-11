
#include "Shapes.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

#define VEC(X...) std::vector<Oedon::VertexId>{{X}}

namespace Oedon
{
    static const glm::vec3 POS_X(1.0f, 0.0f, 0.0f);
    static const glm::vec3 POS_Y(0.0f, 1.0f, 0.0f);
    static const glm::vec3 POS_Z(0.0f, 0.0f, 1.0f);
    static const glm::vec3 NEG_X = -POS_X;
    static const glm::vec3 NEG_Y = -POS_Y;
    static const glm::vec3 NEG_Z = -POS_Z;

    static void TranslatePoints(std::vector<Vertex>& buffer, const glm::vec3& dir)
    {
        //glm::mat4 transform = glm::translate(glm::mat4(1.0f), dir);

        for(auto& vertex : buffer)
        {
            //vertex.pos = glm::vec3(glm::vec4(vertex.pos, 1.0f) * transform);
            //vertex.pos += dir;
        }
    }

    void Plane(std::vector<Vertex>& buffer, const glm::vec3& normal, float size)
    {
        /*
        // Since we allow any arbitrary normal for the plane, create a rotation matrix that will rotate points
        glm::quat rot = glm::rotation(glm::vec3(0.0, 0.0, 1.0), (normal.z == 0.0f) ? -normal : normal);

        //glm::mat4 rot(1.0f);

        float halfSize = size / 2.0f;

        // First face
        buffer.emplace_back(Vertex{glm::vec3(-halfSize, -halfSize, 0.0f) * rot, normal, glm::vec2()});
        buffer.emplace_back(Vertex{glm::vec3(halfSize, -halfSize, 0.0f) * rot, normal, glm::vec2()});
        buffer.emplace_back(Vertex{glm::vec3(halfSize, halfSize, 0.0f) * rot, normal, glm::vec2()});

        // Second face
        buffer.emplace_back(Vertex{glm::vec3(-halfSize, -halfSize, 0.0f)* rot, normal, glm::vec2()});
        buffer.emplace_back(Vertex{glm::vec3(halfSize, halfSize, 0.0f)* rot, normal, glm::vec2()});
        buffer.emplace_back(Vertex{glm::vec3(-halfSize, halfSize, 0.0f) * rot, normal, glm::vec2()});
         */
    }

    Mesh Cube(float size)
    {
        const float halfSize = size / 2.0f;

        Mesh m{};
        const VertexId A = m.AddVertex(glm::vec3(-halfSize, halfSize, halfSize));
        const VertexId B = m.AddVertex(glm::vec3(halfSize, halfSize, halfSize));
        const VertexId C = m.AddVertex(glm::vec3(halfSize, halfSize, -halfSize));
        const VertexId D = m.AddVertex(glm::vec3(-halfSize, halfSize, -halfSize));

        const VertexId E = m.AddVertex(glm::vec3(-halfSize, -halfSize, halfSize));
        const VertexId F = m.AddVertex(glm::vec3(halfSize, -halfSize, halfSize));
        const VertexId G = m.AddVertex(glm::vec3(halfSize, -halfSize, -halfSize));
        const VertexId H = m.AddVertex(glm::vec3(-halfSize, -halfSize, -halfSize));

        m.AddFace(VEC(A, B, C, D));
        m.AddFace(VEC(E, H, G, F));
        m.AddFace(VEC(A, E, F, B));
        m.AddFace(VEC(D, C, G, H));
        m.AddFace(VEC(A, D, H, E));
        m.AddFace(VEC(F, G, C, B));

        /*const float halfSize = size / 2.0f;

        Mesh m{};
        m.verticies.emplace_back(glm::vec3(-halfSize, halfSize, halfSize));   // A
        m.verticies.emplace_back(glm::vec3(halfSize, halfSize, halfSize));   // B
        m.verticies.emplace_back(glm::vec3(halfSize, halfSize, -halfSize));   // C
        m.verticies.emplace_back(glm::vec3(-halfSize, halfSize, -halfSize));  // D

        m.verticies.emplace_back(glm::vec3(-halfSize, -halfSize, halfSize));   // E
        m.verticies.emplace_back(glm::vec3(halfSize, -halfSize, halfSize));   // F
        m.verticies.emplace_back(glm::vec3(halfSize, -halfSize, -halfSize));   // G
        m.verticies.emplace_back(glm::vec3(-halfSize, -halfSize, -halfSize));  // H

        // UVs not implemented
        for(int i = 0; i < 8; i++)
        {
            m.uvs.emplace_back(glm::vec2(0.0f));
        }

        const unsigned A = 0;
        const unsigned B = 1;
        const unsigned C = 2;
        const unsigned D = 3;
        const unsigned E = 4;
        const unsigned F = 5;
        const unsigned G = 6;
        const unsigned H = 7;

        // Pos Y face
        m.faces.emplace_back(Face(A, B, C));
        m.faces.emplace_back(Face(A, C, D));
        m.normals.emplace_back(POS_Y);
        m.normals.emplace_back(POS_Y);

        // Neg Y face
        m.faces.emplace_back(Face(E, H, G));
        m.faces.emplace_back(Face(E, G, F));
        m.normals.emplace_back(NEG_Y);
        m.normals.emplace_back(NEG_Y);

        // Pos X face
        m.faces.emplace_back(Face(F, G, B));
        m.faces.emplace_back(Face(G, C, B));
        m.normals.emplace_back(POS_X);
        m.normals.emplace_back(POS_X);

        // Neg X face
        m.faces.emplace_back(Face(E, A, H));
        m.faces.emplace_back(Face(H, A, D));
        m.normals.emplace_back(NEG_X);
        m.normals.emplace_back(NEG_X);

        // Pos Z face
        m.faces.emplace_back(Face(E, F, A));
        m.faces.emplace_back(Face(A, F, B));
        m.normals.emplace_back(POS_Z);
        m.normals.emplace_back(POS_Z);

        // Neg Z face
        m.faces.emplace_back(Face(H, D, G));
        m.faces.emplace_back(Face(D, C, G));
        m.normals.emplace_back(NEG_Z);
        m.normals.emplace_back(NEG_Z); */

        return m;
    }

    glm::vec3 SphericalToCartesian(float m, float p, float r)
    {
        float x = std::sin(m) * std::cos(p) * r;
        float y = std::sin(m) * std::sin(p) * r;
        float z = std::cos(m) * r;

        return {x, y, z};
    }

    Mesh Sphere(std::uint64_t hcount, std::uint64_t vcount, float diameter)
    {
        Mesh mesh{};
        std::vector<std::vector<VertexId>> rows;
        const float radius = diameter / 2.0f;

        {
            std::vector<VertexId> firstVert;
            firstVert.emplace_back(mesh.AddVertex(glm::vec3(0.0f, 0.0f, radius)));
            rows.emplace_back(firstVert);
        }

        for(std::uint64_t i = 1; i < hcount - 1; i++)
        {
            rows.emplace_back(std::vector<VertexId>{});
            auto& row = rows.back();

            float parallel = M_PIf * (static_cast<float>(i + 1)) / static_cast<float>(hcount);

            for(std::uint64_t j = 0; j < vcount; j++)
            {
                float meridian = 2.0f * M_PIf * static_cast<float>(j) / static_cast<float>(vcount);

                row.emplace_back(mesh.AddVertex(SphericalToCartesian(parallel, meridian, radius)));
            }
        }

        {
            std::vector<VertexId> lastVert;
            lastVert.emplace_back(mesh.AddVertex(glm::vec3(0.0f, 0.0f, -radius)));
            rows.emplace_back(lastVert);
        }

        if(hcount < 2 || vcount < 2)
        {
            return mesh;
        }

        for(int v = 0; v < vcount; v++)
        {
            int vnext = v + 1;
            if(vnext == vcount)
            {
                vnext = 0;
            }

            mesh.AddFace(VEC(rows[0][0], rows[1][vnext], rows[1][v]));
            mesh.AddFace(VEC(rows[hcount - 2][vnext], rows[hcount - 1][0], rows[hcount - 2][v]));
        }

        for(int h = 1; h < hcount - 2; h++)
        {
            int hnext = h + 1;

            for(int v = 0; v < vcount; v++)
            {
                int vnext = v + 1;
                if(vnext == vcount)
                {
                    vnext = 0;
                }

                mesh.AddFace(VEC(rows[h][v], rows[h][vnext], rows[hnext][vnext], rows[hnext][v]));
            }
        }

        /*for(int h = 1; h < hcount - 1; h++)
        {
            int hnext = h + 1;

            for(int v = 0; v < vcount; v++)
            {
                int vnext = v + 1;
                if(vnext == vcount)
                {
                    vnext = 0;
                }

                mesh.AddFace(VEC(rows[h][v], rows[h][vnext], rows[hnext][vnext], rows[hnext][v]));
            }
        }*/

#if 0
        for(auto rowIt = rows.begin() + 1; rowIt != rows.end(); rowIt++)
        {
            auto& row = *rowIt;
            auto& prevRow = *(rowIt - 1);


            for(auto verIt = row.begin(); verIt != row.end(); verIt++)
            {
                auto verNext = verIt++;
                if(verNext == row.end())
                {
                    verNext = row.begin();
                }

                size_t verIndex = std::distance(row.begin(), verIt);
                size_t verNextIndex = std::distance(row.begin(), verNext);

                VertexId A = prevRow[verIndex];
                VertexId B = prevRow[verNextIndex];
                VertexId C = *verNext;
                VertexId D = *verIt;

                mesh.AddFace(VEC(A, B, C, D));
            }
        }
#endif

        return mesh;
    }
}
