#include "main.h"
#include <fstream>
#include <vector>

App::App()
    : m_pWnd{nullptr}
    , m_pGlContext{nullptr}
    , m_iProgram{0}
    , m_iBuffer{0}
    , m_iCellCount{0}
    , m_bRun{false}
    , m_frameTime{std::chrono::nanoseconds(0)}
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw "SDL_INIT";
    if (!(m_pWnd = CreateWindow()))
        throw "CreateWindow";
    if (!(m_pGlContext = SDL_GL_CreateContext(m_pWnd)))
        throw "SDL_GL_CreateContext";
	if(! (m_iProgram = CreateShader()))
        throw "CreateGlProgram";
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
        400, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}

GLuint App::CreateShader()
{
    int iProgram = glCreateProgram();
	if (iProgram == 0)
		return 0;

	GLint Result = GL_FALSE;

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    char const * VertexSourcePointer = _binary_src_shader_vertex_glsl_start;
    GLint VertexSourceLength = _binary_src_shader_vertex_glsl_end - _binary_src_shader_vertex_glsl_start;
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, &VertexSourceLength);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	if (Result != GL_TRUE)
		return -1;
	glAttachShader(iProgram, VertexShaderID);

	GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
    char const * GeometrySourcePointer = _binary_src_shader_geometry_glsl_start;
    GLint GeometrySourceLength = _binary_src_shader_geometry_glsl_end - _binary_src_shader_geometry_glsl_start;
	glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, &GeometrySourceLength);
	glCompileShader(GeometryShaderID);
	glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
	if (Result != GL_TRUE)
		return -1;
	glAttachShader(iProgram, GeometryShaderID);

	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    char const * FragmentSourcePointer = _binary_src_shader_fragment_glsl_start;
    GLint FragmentSourceLength = _binary_src_shader_fragment_glsl_end - _binary_src_shader_fragment_glsl_start;
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, &FragmentSourceLength);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	if (Result != GL_TRUE)
		return -1;
	glAttachShader(iProgram, FragmentShaderID);

	glLinkProgram(iProgram);
	glGetProgramiv(iProgram, GL_LINK_STATUS, &Result);
	if (Result != GL_TRUE)
		return 0;

	glDetachShader(iProgram, VertexShaderID);
	glDetachShader(iProgram, GeometryShaderID);
	glDetachShader(iProgram, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(GeometryShaderID);
	glDeleteShader(FragmentShaderID);

	glUseProgram(iProgram);
	return iProgram;
}

bool App::InitGl()
{
	glDisable(GL_PROGRAM_POINT_SIZE);
	glPointSize(8);
    SetGlView();
    GLuint VertexArray;
    glGenVertexArrays(1, &VertexArray);
	if (VertexArray == 0)
		return false;
	glBindVertexArray(VertexArray);
    return true;
}

void App::SetGlView()
{
    int w, h;
    SDL_GetWindowSize(m_pWnd, &w, &h);
	glViewport( 0, 0, w, h);
}

App::~App()
{
    SDL_GL_DeleteContext(m_pGlContext);
	SDL_DestroyWindow(m_pWnd);
	SDL_Quit();
}

int App::Run(int argc, char* argv[])
{
    for(;;)
    {
        SDL_Event event;
        int bEvent;
        if (m_bRun)
        {
             Tick();
            bEvent = SDL_WaitEventTimeout(&event, 333);
        }
        else
            bEvent = SDL_WaitEvent(&event);
        if (bEvent)
        {
            if (event.type == SDL_QUIT)
                break;
            else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                SetGlView();
                if (m_bRun == false && m_iCellCount > 0)
                    Tick();
            }
            else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                {
                    ToggleRun();
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_L)
                {
                    if (!m_bRun)
                    {
                        if (Load())
                            Tick();
                    }
                }    
                else if (event.key.keysym.scancode == SDL_SCANCODE_S)
                {
                    if (!m_bRun)
                    {
                        if (Save())
                        {
                        }
                    }
                }    
            }
        }
    }
    return 0;
}

void App::Tick()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_POINTS, 0, m_iCellCount);
    glFinish();
    SDL_GL_SwapWindow(m_pWnd);
}

void App::ToggleRun()
{
    m_bRun = !m_bRun;
    glUniform1i(glGetUniformLocation(m_iProgram, "run"), m_bRun);
    if (m_bRun)
        m_frameTime = std::chrono::steady_clock::now();
}

bool App::Load()
{
    std::ifstream img(GetFileName());
    char sign[3] = {0};
    if (img)
        img >> sign[0] >> sign[1];
    if (strcmp(sign, "P1") != 0)
        return false;
    int iWidth, iHeight;
    if (img)
        img >> iWidth;
    if (img)
        img >> iHeight;
    if (iWidth <= 0 || iWidth > 0x1000 || iHeight <= 0 || iHeight > 0x1000)
        return false;
    std::vector<GLint> vCell(iWidth * iHeight);
    for (int y = 0; y < iHeight; ++y)
    {
        for (int x = 0; x < iWidth; ++x)
        {
            if (!img)
                return false;
            img >> vCell[y * iWidth + x];
        }
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, vCell.size() * sizeof(GLint),
        vCell.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_iBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glUniform1i(glGetUniformLocation(m_iProgram, "width"), iWidth);
    glUniform1i(glGetUniformLocation(m_iProgram, "height"), iHeight);
    m_iCellCount = iWidth * iHeight;
    return true;
}

bool App::Save()
{
    std::ofstream img(GetFileName());
    return true;
}

std::string App::GetFileName()
{
    char file[1024];
	FILE *f = popen("zenity --file-selection", "r");
	fgets(file, 1024, f);
	pclose(f);
	file[strlen(file) - 1] = 0;
    return file;
}


int main(int argc, char* argv[])
{
    App app;
    return app.Run(argc, argv);
}