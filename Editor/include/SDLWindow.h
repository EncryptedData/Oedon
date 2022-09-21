
struct SDL_Window;

namespace Oedon::Editor
{
    class SDLWindow
    {
    public:
        explicit SDLWindow();

        ~SDLWindow();

        void Update();

        bool ShouldContinue() const;

        void StartFrame() const;

        void EndFrame() const;

    private:
        SDL_Window* _window;
        void* _glContext;
        bool _shouldContinue;
    };
}
