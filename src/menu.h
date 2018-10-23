#pragma once

#include "context.hpp"

extern const char _binary_src_shader_menu_vertex_glsl_end[];
extern const char _binary_src_shader_menu_vertex_glsl_start[];

extern const char _binary_src_shader_menu_fragment_glsl_end[];
extern const char _binary_src_shader_menu_fragment_glsl_start[];

class Menu: public Context<Menu>
{
private:
	GLuint m_iVertexArray;

public:
	Menu(SDL_Window* pWnd);
	~Menu();

	void Tick(int64_t iRealSpeed, int64_t iNominalSpeed);
	const char* GetVertexStart();
	const char* GetVertexEnd();
	const char* GetFragmentStart();
	const char* GetFragmentEnd();
};
