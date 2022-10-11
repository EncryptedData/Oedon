
set(OEDON_EDITOR_SRC
        src/main.cpp
        src/SDLWindow.cpp
        src/MainWindowView.cpp
        src/BlueprintView.cpp
        src/BlueprintViewModel.cpp
        src/GpuMesh.cpp
        src/Shader.cpp
        src/Framebuffer.cpp
        src/SceneView.cpp
        src/SceneViewModel.cpp
        src/NodeFactory.cpp
        src/nodes/MeshNode.cpp
        src/EventDispatcher.cpp
        src/MainWindowViewModel.cpp src/nodes/MeshTransformNode.cpp src/PropertiesView.cpp src/nodes/ConstantNode.cpp src/nodes/LineLerper.cpp)

add_executable(oedon-editor ${OEDON_EDITOR_SRC})
target_link_libraries(oedon-editor PUBLIC
        imgui
        SDL2::SDL2
        glbinding
        glm
        oedon)

target_compile_features(oedon-editor PUBLIC cxx_std_17)

target_include_directories(oedon-editor PUBLIC include)
