#pragma once

namespace Oedon::Editor
{
    class Framebuffer
    {
    public:

        void Create(int w, int h);

        void Resize(int w, int h);

        void Clear();

        void Bind();

        void Unbind();

        unsigned GetColorTexture() const;

    private:
        unsigned _fbo;
        unsigned _color;
        unsigned _depth;
        int _width;
        int _height;
    };
}
