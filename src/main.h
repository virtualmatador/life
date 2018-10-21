#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <chrono>
#include <string>

extern const char _binary_src_shader_vertex_glsl_end[];
extern const char _binary_src_shader_vertex_glsl_start[];

extern const char _binary_src_shader_fragment_glsl_end[];
extern const char _binary_src_shader_fragment_glsl_start[];

class Life
{
private:
    SDL_Window* m_pWnd;
    SDL_GLContext m_pGlContext;

    GLuint m_iProgram;
    GLuint m_iVertexArray;
    GLuint m_iBuffers[2];
    bool m_bSwap;
    bool m_bRun;
    std::chrono::steady_clock::time_point m_frameTime;

    int m_iCx;
    int m_iCy;
    int m_iWidth;
    int m_iHeight;
    int64_t m_iDelay;

public:
    Life();
    ~Life();
    int Run(int argc, char* argv[]);

private:
    SDL_Window* CreateWindow();
    GLuint CreateShader();
    bool InitGl();
    void SetGlView();
    void SetPointSize();
    void Tick();
    void SetBufferBase();
    bool Load();
    bool Save();
    std::string GetFileName(bool bSave);
    void QuitGl();
};
