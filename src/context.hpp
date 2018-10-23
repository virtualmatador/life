#pragma once

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

template <typename T>
class Context
{
protected:
	SDL_GLContext m_pContext;
	SDL_Window* m_pWnd;
	GLuint m_iProgram;

public:
	Context(SDL_Window* pWnd);
	~Context();

	void SetWindowSize();
};

template<typename T>
Context<T>::Context(SDL_Window* pWnd)
	: m_pWnd{pWnd}
	, m_iProgram{0}
{
	m_pContext = SDL_GL_CreateContext(m_pWnd);
	if (!m_pContext)
		throw "SDL_GL_CreateContext";

	m_iProgram = glCreateProgram();
	if (m_iProgram == 0)
		throw "glCreateProgram";

	GLint Result = GL_FALSE;

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	char const * VertexSourcePointer = ((T*)this)->GetVertexStart();
	GLint VertexSourceLength = ((T*)this)->GetVertexEnd() - VertexSourcePointer;
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, &VertexSourceLength);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	if (Result != GL_TRUE)
		throw "glCompileShader";
	glAttachShader(m_iProgram, VertexShaderID);

	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	char const * FragmentSourcePointer = ((T*)this)->GetFragmentStart();
	GLint FragmentSourceLength = ((T*)this)->GetFragmentEnd() - FragmentSourcePointer;
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, &FragmentSourceLength);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	if (Result != GL_TRUE)
		throw "glCompileShader";
	glAttachShader(m_iProgram, FragmentShaderID);

	glLinkProgram(m_iProgram);
	glGetProgramiv(m_iProgram, GL_LINK_STATUS, &Result);
	if (Result != GL_TRUE)
		throw "glLinkProgram";

	glDetachShader(m_iProgram, VertexShaderID);
	glDetachShader(m_iProgram, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	glUseProgram(m_iProgram);
}

template<typename T>
Context<T>::~Context()
{
	SDL_GL_DeleteContext(m_pContext);
}

template<typename T>
void Context<T>::SetWindowSize()
{
	int iWidth, iHeight;
	SDL_GetWindowSize(m_pWnd, &iWidth, &iHeight);
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	glViewport(0, 0, iWidth, iHeight);
}
