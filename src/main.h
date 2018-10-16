#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

class App
{
private:
    SDL_Window* m_pWnd;
    SDL_GLContext m_pGlContext;

public:
    App();
    ~App();
    int Run(int argc, char* argv[]);

private:
    SDL_Window* CreateWindow();
    bool InitGl();
};