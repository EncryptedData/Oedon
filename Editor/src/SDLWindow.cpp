//
// Created by Russell Johnson on 9/4/22.
//

#include "SDLWindow.h"

#include <cassert>
#include <SDL.h>
#include <glbinding/glbinding.h>
#include <imgui_impl_sdl.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <glbinding/gl46core/gl.h>

namespace Oedon::Editor
{
    SDLWindow::SDLWindow() :
        _shouldContinue{true}
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            assert(false);
        }

        _window = SDL_CreateWindow("Oedon Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   1280, 720, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

        if(!_window)
        {
            assert(false);
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        _glContext = SDL_GL_CreateContext(_window);

        if(!_glContext)
        {
            assert(false);
        }

        SDL_GL_MakeCurrent(_window, _glContext);

        SDL_GL_SetSwapInterval(1);

        glbinding::initialize([](const char* addr) {return (glbinding::ProcAddress)SDL_GL_GetProcAddress(addr); });
        gl::glEnable(gl::GLenum::GL_PROGRAM_POINT_SIZE);
        ImGui::CreateContext();
        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(_window, _glContext);
        ImGui_ImplOpenGL3_Init("#version 150");
    }

    void SDLWindow::Update()
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);

            switch(event.type)
            {
                case SDL_QUIT:
                    _shouldContinue = false;
                    break;
            }
        }
    }

    bool SDLWindow::ShouldContinue() const
    {
        return _shouldContinue;
    }

    void SDLWindow::EndFrame() const
    {
        auto& io = ImGui::GetIO();

        ImGui::Render();
        gl::glViewport(0,0, io.DisplaySize.x, io.DisplaySize.y);
        gl::glClearColor(0,0,0,1);
        gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(_window);
    }

    void SDLWindow::StartFrame() const
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    SDLWindow::~SDLWindow()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        if(_glContext)
        {
            SDL_GL_DeleteContext(_glContext);
        }

        if(_window)
        {
            SDL_DestroyWindow(_window);
        }

        SDL_Quit();
    }
}


