cmake_minimum_required(VERSION 3.15)

project(oedon)

include(CMake/CPM.cmake)

option(OEDON_EDITOR "Enable GUI Editor" OFF)
option(OEDON_DOWNLOAD_DEPS "Use CPM to auto download dependencies" ON)

if(OEDON_DOWNLOAD_DEPS)
    CPMAddPackage("gh:/g-truc/glm#0.9.9.8")
    CPMAddPackage("gh:/cginternals/glbinding#v3.1.0")
    #CPMAddPackage("gl:/libeigen/eigen#3.4.0")
    #CPMAddPackage(
    #        NAME pmp-library
    #        VERSION 2.0.1
    #        GITHUB_REPOSITORY pmp-library/pmp-library
    #        GIT_TAG "2.0.1"
    #        OPTIONS "PMP_BUILD_EXAMPLES OFF" "PMP_BUILD_TESTS OFF" "PMP_BUILD_DOCS OFF" "PMP_BUILD_VIS OFF" "PMP_INSTALL OFF"
    #)
    CPMAddPackage(
            NAME openmesh
            VERSION 9.0
            GIT_REPOSITORY "https://gitlab.vci.rwth-aachen.de:9000/OpenMesh/OpenMesh.git"
            GIT_TAG "OpenMesh-9.0"
    )

    if(OEDON_EDITOR)
        CPMAddPackage("gh:/libsdl-org/SDL#release-2.24.0")
    endif()
endif()

find_package(SDL REQUIRED)
find_package(glbinding REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(Dependencies)

add_subdirectory(Oedon)

if(OEDON_EDITOR)
    add_subdirectory(Editor)
endif()
