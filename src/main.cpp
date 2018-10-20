#include "main.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

Life::Life()
    : m_pWnd{nullptr}
    , m_pGlContext{nullptr}
    , m_iProgram{0}
    , m_iVertexArray{0}
    , m_iBuffers{0, 0}
    , m_bSwap{false}
    , m_bRun{false}
    , m_frameTime{std::chrono::nanoseconds(0)}
    , m_iCx{0}
    , m_iCy{0}
    , m_iWidth{0}
    , m_iHeight{0}
    , m_iDelay{33333333}
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
    Tick();
}

SDL_Window* Life::CreateWindow()
{
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0 ||
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5) < 0 ||
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
	    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
        return nullptr;
	return SDL_CreateWindow("Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}

GLuint Life::CreateShader()
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
	glDetachShader(iProgram, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	glUseProgram(iProgram);
	return iProgram;
}

bool Life::InitGl()
{
	glDisable(GL_PROGRAM_POINT_SIZE);
    SetGlView();
    glGenVertexArrays(1, &m_iVertexArray);
	if (m_iVertexArray == 0)
		return false;
	glBindVertexArray(m_iVertexArray);
    glGenBuffers(2, m_iBuffers);
	if (m_iBuffers[0] == 0 || m_iBuffers[1] == 0)
		return false;
    return true;
}

void Life::SetGlView()
{
    SDL_GetWindowSize(m_pWnd, &m_iCx, &m_iCy);
	glViewport( 0, 0, m_iCx, m_iCy);
    SetPointSize();
}

void Life::SetPointSize()
{
    if (m_iWidth * m_iHeight > 0)
    	glPointSize(std::min(m_iCx / (m_iWidth + 2) * 0.75, m_iCy / (m_iHeight + 2) * 0.75));
}

Life::~Life()
{
    QuitGl();
    SDL_GL_DeleteContext(m_pGlContext);
	SDL_DestroyWindow(m_pWnd);
	SDL_Quit();
    std::cout << std::endl;
}

void Life::QuitGl()
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_iVertexArray);
    glDeleteBuffers(2, m_iBuffers);
}

int Life::Run(int argc, char* argv[])
{
    for(;;)
    {
        SDL_Event event;
        int bEvent;
        if (m_bRun)
        {
            auto wait = m_frameTime - std::chrono::steady_clock::now();
            if (wait.count() < 0)
            {
                Tick();
                m_frameTime += std::chrono::nanoseconds(std::max(m_iDelay, -wait.count()));
                bEvent = SDL_PollEvent(&event);
            }
            else
                bEvent = SDL_WaitEventTimeout(&event, wait.count() / 1000000);
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
                if (m_bRun == false)
                    Tick();
            }
            else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
                {
                    if (!m_bRun)
                    {
                        m_frameTime = std::chrono::steady_clock::now();
                        m_bRun = true;
                    }
                    Tick();
                    m_bRun = false;
                    Tick();
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                {
                    m_bRun = !m_bRun;
                    if (m_bRun)
                        m_frameTime = std::chrono::steady_clock::now();
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
                else if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                    if (m_bRun)
                    {
                        m_frameTime -= std::chrono::nanoseconds(m_iDelay);
                        m_iDelay = m_iDelay * 8 / 10;
                        m_frameTime += std::chrono::nanoseconds(m_iDelay);
                    }
                }    
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                    if (m_bRun && m_iDelay < 100000000000)
                    {
                        m_frameTime -= std::chrono::nanoseconds(m_iDelay);
                        m_iDelay = (m_iDelay + 1) * 10 / 8;
                        m_frameTime += std::chrono::nanoseconds(m_iDelay);
                    }
                }    
            }
        }
    }
    return 0;
}

void Life::Tick()
{
    static std::chrono::steady_clock::time_point RefreshTime(std::chrono::nanoseconds(0));
    static int64_t FrameCount = 0;
    ++FrameCount;
    int64_t duration = (m_frameTime - RefreshTime).count();
    bool bRasterize;
    if (m_bRun)
    {
        m_bSwap = !m_bSwap;
        bRasterize = duration > 50000000;
    }
    else
        bRasterize = true;
    SetBufferBase();
    if (bRasterize)
        glDisable(GL_RASTERIZER_DISCARD);
    else
        glEnable(GL_RASTERIZER_DISCARD);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_POINTS, 0, m_iWidth * m_iHeight);
    glFinish();
    if (bRasterize)
    {
        if (duration > 0)
            std::cout << "Delay = " << std::setw(12) << m_iDelay << ", Fps = " << std::setw(8) << FrameCount * 1000000000 / duration << " " << "\e[A" << std::endl;
        FrameCount = 0;
        RefreshTime = m_frameTime;
        SDL_GL_SwapWindow(m_pWnd);
    }
}

void Life::SetBufferBase()
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bSwap, m_iBuffers[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1 - m_bSwap, m_iBuffers[1]);
}

bool Life::Load()
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
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iBuffers[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, vCell.size() * sizeof(GLint),
        vCell.data(), GL_DYNAMIC_COPY);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iBuffers[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, vCell.size() * sizeof(GLint),
        nullptr, GL_DYNAMIC_COPY);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    m_bSwap = false;
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    glUniform1i(glGetUniformLocation(m_iProgram, "width"), m_iWidth);
    glUniform1i(glGetUniformLocation(m_iProgram, "height"), m_iHeight);
    SetPointSize();
    return true;
}

bool Life::Save()
{
    std::ofstream img(GetFileName());
    return true;
}

std::string Life::GetFileName()
{
    char file[1024];
	FILE *f = popen("zenity --file-selection  2>/dev/null", "r");
	fgets(file, 1024, f);
	pclose(f);
	file[strlen(file) - 1] = 0;
    return file;
}

int main(int argc, char* argv[])
{
    Life life;
    return life.Run(argc, argv);
}