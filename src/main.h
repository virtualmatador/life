#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <chrono>
#include <string>

extern const char _binary_src_shader_vertex_glsl_end[];
extern const char _binary_src_shader_vertex_glsl_start[];

extern const char _binary_src_shader_geometry_glsl_end[];
extern const char _binary_src_shader_geometry_glsl_start[];

extern const char _binary_src_shader_fragment_glsl_end[];
extern const char _binary_src_shader_fragment_glsl_start[];

class App
{
private:
    SDL_Window* m_pWnd;
    SDL_GLContext m_pGlContext;

    GLuint m_iProgram;
    GLuint m_iBuffer;
    int m_iCellCount;
    bool m_bRun;
    std::chrono::steady_clock::time_point m_frameTime;

public:
    App();
    ~App();
    int Run(int argc, char* argv[]);

private:
    SDL_Window* CreateWindow();
    GLuint CreateShader();
    bool InitGl();
    void SetGlView();
    void Tick();
    void ToggleRun();
    bool Load();
    bool Save();
    std::string GetFileName();
};