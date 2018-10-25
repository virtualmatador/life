#pragma once

#include "context.hpp"
#include "control.h"

#include <string>
#include <list>

extern const char _binary_src_shader_menu_vertex_glsl_end[];
extern const char _binary_src_shader_menu_vertex_glsl_start[];

extern const char _binary_src_shader_menu_geometry_glsl_end[];
extern const char _binary_src_shader_menu_geometry_glsl_start[];

extern const char _binary_src_shader_menu_fragment_glsl_end[];
extern const char _binary_src_shader_menu_fragment_glsl_start[];

class Menu: public Context<Menu>
{
private:
	GLuint m_iVertexArray;
	GLuint m_iFontBuffer;
	GLuint m_iTextBuffer;

	static const float m_arFont[][8][2];
	int m_iCharCount;
	std::list<Control> m_lstControl;

	std::string* m_pRealSpeed;
	std::string* m_pNominalSpeed;

public:
	Menu(Life* pApp);
	~Menu();

	SDL_Window* GetWindow();
	void UploadTexts();
	void Tick(bool bUpdate, double dRealSpeed, double dNominalSpeed);
	bool HitTest(int x, int y);
	const char* GetVertexStart();
	const char* GetVertexEnd();
	const char* GetGeometryStart();
	const char* GetGeometryEnd();
	const char* GetFragmentStart();
	const char* GetFragmentEnd();
};
