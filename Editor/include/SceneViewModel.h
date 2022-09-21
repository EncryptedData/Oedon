#pragma once

#include <glm/vec3.hpp>
#include "Framebuffer.h"
#include "GpuMesh.h"
#include "Shapes.h"
#include "Shader.h"

#include "EventDispatcher.h"
#include "Events.h"

#include <memory>

namespace Oedon::Editor
{
    struct SceneViewModel : ListenFor<NodeSelectionChangedEvent>, ListenFor<RefreshSceneViewEvent>
    {
        explicit SceneViewModel(EventDispatcher* dispatcher);

        void Init();

        glm::vec3 camera_pos;
        glm::vec3 camera_dir;

        std::shared_ptr<GpuMesh> mesh;
        std::shared_ptr<Framebuffer> framebuffer;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<Shader> pointsShader;
        std::shared_ptr<Shader> currentShader;

    private:
        void OnEvent(NodeSelectionChangedEvent &event) override;
        void OnEvent(RefreshSceneViewEvent &event) override;

        void ProcessNodeMesh(const std::shared_ptr<NodeVM>& node);
    };
}
