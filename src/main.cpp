#include "main.h"

App::App()
    : m_pWnd{nullptr}
    , m_pGlContext{nullptr}
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw "SDL_INIT";
    if (!(m_pWnd = CreateWindow()))
        throw "SDL_CreateWindow";
    if (!(m_pGlContext = SDL_GL_CreateContext(m_pWnd)))
        throw "SDL_GL_CreateContext";
	if(!InitGl())
        throw "InitGl";
}

SDL_Window* App::CreateWindow()
{
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0 ||
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5) < 0 ||
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
	    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
        return nullptr;
	return SDL_CreateWindow("Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}

bool App::InitGl()
{
    int w, h;
    SDL_GetWindowSize(m_pWnd, &w, &h);
	glViewport( 0, 0, w, h);
	glDisable(GL_PROGRAM_POINT_SIZE);
	glPointSize(8);
    return true;
}

App::~App()
{
    SDL_GL_DeleteContext(m_pGlContext);
	SDL_DestroyWindow(m_pWnd);
	SDL_Quit();
}

int App::Run(int argc, char* argv[])
{
    return 0;
}

int main(int argc, char* argv[])
{
    App app;
    return app.Run(argc, argv);
}