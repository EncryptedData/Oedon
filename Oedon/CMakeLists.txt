
set(OEDON_SRC
        src/stub.cpp
        src/Shapes.cpp
        src/DataVariant.cpp src/Mesh.cpp src/FatVertex.cpp)

add_library(oedon ${OEDON_SRC})

target_include_directories(oedon PUBLIC include)
target_compile_features(oedon PUBLIC cxx_std_17)
target_link_libraries(oedon PUBLIC glm )
