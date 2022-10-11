
#include "SceneViewModel.h"
#include "BlueprintViewModel.h"

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace Oedon::Editor
{
    static std::string ReadAllFromFile(std::string_view path)
    {
        std::ifstream stream(path.data());
        std::stringstream buffer;
        buffer << stream.rdbuf();

        return buffer.str();
    }

    void SceneViewModel::Init()
    {
        camera_pos = glm::vec3(25.0f, 25.0f, 25.0f);
        camera_dir = glm::normalize(-camera_pos);

        framebuffer = std::make_shared<Framebuffer>();
        framebuffer->Create(100, 100);

        shader = std::make_shared<Shader>();
        std::string shaderStr = ReadAllFromFile("Resources/Shaders/default.vert.glsl");
        assert(!shaderStr.empty());
        shader->Compile(shaderStr, ShaderType::Vertex);

        shaderStr = ReadAllFromFile("Resources/Shaders/debug.normals.frag.glsl");
        assert(!shaderStr.empty());
        shader->Compile(shaderStr, ShaderType::Fragment);

        shader->Link();

        pointsShader = std::make_shared<Shader>();
        shaderStr = ReadAllFromFile("Resources/Shaders/points.vert.glsl");
        assert(!shaderStr.empty());
        pointsShader->Compile(shaderStr, ShaderType::Vertex);

        shaderStr = ReadAllFromFile("Resources/Shaders/debug.frag.glsl");
        assert(!shaderStr.empty());
        pointsShader->Compile(shaderStr, ShaderType::Fragment);

        pointsShader->Link();
    }

    void SceneViewModel::OnEvent(NodeSelectionChangedEvent &event)
    {
        ProcessNodeMesh(event.node);
    }

    SceneViewModel::SceneViewModel(EventDispatcher *dispatcher) :
        ListenFor<RefreshSceneViewEvent>(dispatcher),
        ListenFor<NodeSelectionChangedEvent>(dispatcher)
    {
    }

    void SceneViewModel::OnEvent(RefreshSceneViewEvent &event)
    {
        ProcessNodeMesh(event.node);
    }



    void SceneViewModel::ProcessNodeMesh(const std::shared_ptr<NodeVM>& node)
    {
        mesh.reset();

        if(node && !node->outputPins.empty())
        {
            const auto& pin = node->outputPins[0];

            if(pin->cache.has_value())
            {
                switch(pin->cache->type)
                {
                    case DataVariantType::Mesh:
                    {
                        std::vector<FatVertex> verts;
                        //ToVertecies(verts, pin->cache->mesh);

                        ToFatVerticies(verts, pin->cache->mesh);

                        mesh = std::make_shared<GpuMesh>(verts);
                        currentShader = shader;
                        break;
                    }

                    case DataVariantType::Points:
                    {
                        mesh = std::make_shared<GpuMesh>(pin->cache->points);
                        currentShader = pointsShader;
                        break;
                    }
                    case DataVariantType::Empty:
                        break;
                }


            }
        }
    }
}

