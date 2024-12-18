#ifndef SRC_CONTEXT_HPP
#define SRC_CONTEXT_HPP

#include <SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>

class Life;

template <typename T>
class Context
{
protected:
	SDL_GLContext m_pContext;
	Life *m_pApp;
	GLuint m_iProgram;

public:
	Context(Life *pApp);
	~Context();

	void SetWindowSize();
};

template <typename T>
Context<T>::Context(Life *pApp)
	: m_pApp{pApp}, m_iProgram{0}
{
	m_pContext = SDL_GL_CreateContext(((T *)this)->GetWindow());
	if (!m_pContext)
		throw "SDL_GL_CreateContext";

	SDL_GL_MakeCurrent(((T *)this)->GetWindow(), m_pContext);
	glewInit();

	m_iProgram = glCreateProgram();
	if (m_iProgram == 0)
		throw "glCreateProgram";

	GLint Result = GL_FALSE;

	auto VertexSourcePointer = ((T *)this)->GetVertexStart();
	GLint VertexSourceLength = ((T *)this)->GetVertexSize();
	GLuint VertexShaderID = 0;
	if (VertexSourceLength > 0)
	{
		VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, &VertexSourceLength);
		glCompileShader(VertexShaderID);
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		if (Result != GL_TRUE)
			throw "glCompileShader GL_VERTEX_SHADER";
		glAttachShader(m_iProgram, VertexShaderID);
	}

	auto GeometrySourcePointer = ((T *)this)->GetGeometryStart();
	GLint GeometrySourceLength = ((T *)this)->GetGeometrySize();
	GLuint GeometryShaderID = 0;
	if (GeometrySourceLength > 0)
	{
		GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, &GeometrySourceLength);
		glCompileShader(GeometryShaderID);
		glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
		if (Result != GL_TRUE)
			throw "glCompileShader GL_GEOMETRY_SHADER";
		glAttachShader(m_iProgram, GeometryShaderID);
	}

	auto FragmentSourcePointer = ((T *)this)->GetFragmentStart();
	GLint FragmentSourceLength = ((T *)this)->GetFragmentSize();
	GLuint FragmentShaderID = 0;
	if (FragmentSourceLength > 0)
	{
		FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, &FragmentSourceLength);
		glCompileShader(FragmentShaderID);
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		if (Result != GL_TRUE)
			throw "glCompileShader GL_FRAGMENT_SHADER";
		glAttachShader(m_iProgram, FragmentShaderID);
	}

	glLinkProgram(m_iProgram);
	glGetProgramiv(m_iProgram, GL_LINK_STATUS, &Result);
	if (Result != GL_TRUE)
		throw "glLinkProgram";

	if (VertexShaderID)
	{
		glDetachShader(m_iProgram, VertexShaderID);
		glDeleteShader(VertexShaderID);
	}
	if (GeometryShaderID)
	{
		glDetachShader(m_iProgram, GeometryShaderID);
		glDeleteShader(GeometryShaderID);
	}
	if (FragmentShaderID)
	{
		glDetachShader(m_iProgram, FragmentShaderID);
		glDeleteShader(FragmentShaderID);
	}

	glUseProgram(m_iProgram);
}

template <typename T>
Context<T>::~Context()
{
	SDL_GL_DeleteContext(m_pContext);
}

template <typename T>
void Context<T>::SetWindowSize()
{
	SDL_GL_MakeCurrent(((T *)this)->GetWindow(), m_pContext);
	glViewport(0, 0, ((T *)this)->m_pApp->m_ptClient.x, ((T *)this)->m_pApp->m_ptClient.y);
}

#endif // SRC_CONTEXT_HPP
