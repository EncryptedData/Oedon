
set(IMGUI_SRC
        crude_json.cpp
        imgui.cpp
        imgui_canvas.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_impl_opengl3.cpp
        imgui_impl_sdl.cpp
        imgui_node_editor.cpp
        imgui_node_editor_api.cpp
        imgui_tables.cpp
        imgui_widgets.cpp)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC include)
target_compile_features(imgui PRIVATE cxx_std_14)

target_link_libraries(imgui PUBLIC SDL2::SDL2)
