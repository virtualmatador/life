#include "menu.h"

Menu::Menu(SDL_Window* pWnd)
	: Context<Menu>{pWnd}
{
	glDisable(GL_PROGRAM_POINT_SIZE);
	glGenVertexArrays(1, &m_iVertexArray);
	if (m_iVertexArray == 0)
		throw "glGenVertexArrays";
	glBindVertexArray(m_iVertexArray);
	glPointSize(200);
}

Menu::~Menu()
{
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_iVertexArray);
}

void Menu::Tick(int64_t iRealSpeed, int64_t iNominalSpeed)
{
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	glDrawArrays(GL_POINTS, 0, 1);
	glFinish();
}

const char* Menu::GetVertexStart()
{
	return _binary_src_shader_menu_vertex_glsl_start;
}

const char* Menu::GetVertexEnd()
{
	return _binary_src_shader_menu_vertex_glsl_end;
}

const char* Menu::GetFragmentStart()
{
	return _binary_src_shader_menu_fragment_glsl_start;
}

const char* Menu::GetFragmentEnd()
{
	return _binary_src_shader_menu_fragment_glsl_end;
}
