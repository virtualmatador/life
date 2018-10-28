#pragma once

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

class Life;

template <typename T>
class Context
{
protected:
	SDL_GLContext m_pContext;
	Life* m_pApp;
	GLuint m_iProgram;

public:
	Context(Life* pApp);
	~Context();

	void SetWindowSize();
};

template<typename T>
Context<T>::Context(Life* pApp)
	: m_pApp{pApp}
	, m_iProgram{0}
{
	m_pContext = SDL_GL_CreateContext(((T*)this)->GetWindow());
	if (!m_pContext)
		throw "SDL_GL_CreateContext";

	m_iProgram = glCreateProgram();
	if (m_iProgram == 0)
		throw "glCreateProgram";

	GLint Result = GL_FALSE;

	char const * VertexSourcePointer = ((T*)this)->GetVertexStart();
	GLint VertexSourceLength = ((T*)this)->GetVertexEnd() - VertexSourcePointer;
	GLuint VertexShaderID = 0;
	if (VertexSourceLength > 0)
	{
		VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, &VertexSourceLength);
		glCompileShader(VertexShaderID);
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		if (Result != GL_TRUE)
			throw "glCompileShader";
		glAttachShader(m_iProgram, VertexShaderID);
	}

	char const * GeometrySourcePointer = ((T*)this)->GetGeometryStart();
	GLint GeometrySourceLength = ((T*)this)->GetGeometryEnd() - GeometrySourcePointer;
	GLuint GeometryShaderID = 0;
	if (GeometrySourceLength > 0)
	{
		GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, &GeometrySourceLength);
		glCompileShader(GeometryShaderID);
		glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
		if (Result != GL_TRUE)
			throw "glCompileShader";
		glAttachShader(m_iProgram, GeometryShaderID);
	}

	char const * FragmentSourcePointer = ((T*)this)->GetFragmentStart();
	GLint FragmentSourceLength = ((T*)this)->GetFragmentEnd() - FragmentSourcePointer;
	GLuint FragmentShaderID = 0;
	if (FragmentSourceLength > 0)
	{
		FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, &FragmentSourceLength);
		glCompileShader(FragmentShaderID);
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		if (Result != GL_TRUE)
			throw "glCompileShader";
		glAttachShader(m_iProgram, FragmentShaderID);
	}

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
	SDL_GetWindowSize(((T*)this)->GetWindow(), &iWidth, &iHeight);
	SDL_GL_MakeCurrent(((T*)this)->GetWindow(), m_pContext);
	glViewport(0, 0, iWidth, iHeight);
}
