
#include "Shapes.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

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
            vertex.pos += dir;
        }
    }

    void Plane(std::vector<Vertex>& buffer, const glm::vec3& normal, float size)
    {
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
    }

    Mesh Cube(float size)
    {
        const float halfSize = size / 2.0f;

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
        m.normals.emplace_back(NEG_Z);

        return m;
    }
}
