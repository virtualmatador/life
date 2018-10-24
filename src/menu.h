#pragma once

#include "context.hpp"

#include <string>

extern const char _binary_src_shader_menu_vertex_glsl_end[];
extern const char _binary_src_shader_menu_vertex_glsl_start[];

extern const char _binary_src_shader_menu_geometry_glsl_end[];
extern const char _binary_src_shader_menu_geometry_glsl_start[];

extern const char _binary_src_shader_menu_fragment_glsl_end[];
extern const char _binary_src_shader_menu_fragment_glsl_start[];

struct TEXT
{
	std::string text;
	GLfloat fX;
	GLfloat fY;
	GLfloat fScalse;
	GLfloat fColor[3];
};

class Menu: public Context<Menu>
{
private:
	GLuint m_iVertexArray;
	GLuint m_iFontBuffer;
	GLuint m_iTextBuffer;

	static const float m_arFont[][8][2];
	int m_iCharCount;
	TEXT m_Speed;

public:
	Menu(SDL_Window* pWnd);
	~Menu();

	void UploadTexts();
	void Tick(int64_t iRealSpeed, int64_t iNominalSpeed);
	const char* GetVertexStart();
	const char* GetVertexEnd();
	const char* GetGeometryStart();
	const char* GetGeometryEnd();
	const char* GetFragmentStart();
	const char* GetFragmentEnd();

private:
	void UploadText(TEXT & txt, std::stringstream & stream);
};
