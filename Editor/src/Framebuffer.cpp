
#include "Framebuffer.h"

#include <cassert>
#include <glbinding/gl46core/gl.h>

namespace Oedon::Editor
{
    using namespace gl;

    void Framebuffer::Create(int w, int h)
    {
        assert(w > 0);
        assert(h > 0);

        // Build the textures for the framebuffer
        glGenTextures(1, &_color);
        glGenTextures(1, &_depth);

        _width = 0;
        _height = 0;
        Resize(w, h);

        glGenFramebuffers(1, &_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

        // Attach the textures
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _color, 0);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, _depth, 0);
    }

    void Framebuffer::Resize(int w, int h)
    {
        if(w == _width && h == _height)
        {
            return;
        }

        _width = w;
        _height = h;

        glBindTexture(GL_TEXTURE_2D, _color);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, _depth);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    void Framebuffer::Clear()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glViewport(0, 0, _width, _height);
        glClear(ClearBufferMask::GL_DEPTH_BUFFER_BIT | ClearBufferMask::GL_COLOR_BUFFER_BIT);
    }

    void Framebuffer::Bind()
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
    }

    void Framebuffer::Unbind()
    {
        const unsigned DefaultFramebufferId = 0;
        glBindFramebuffer(GL_FRAMEBUFFER, DefaultFramebufferId);
    }

    unsigned Framebuffer::GetColorTexture() const
    {
        return _color;
    }
}

