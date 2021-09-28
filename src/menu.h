#pragma once

#include "context.hpp"
#include "control.h"

#include <string>
#include <list>
#include <chrono>

extern const char _binary_menu_vertex_glsl_end[];
extern const char _binary_menu_vertex_glsl_start[];

extern const char _binary_menu_geometry_glsl_end[];
extern const char _binary_menu_geometry_glsl_start[];

extern const char _binary_menu_fragment_glsl_end[];
extern const char _binary_menu_fragment_glsl_start[];

extern const float arFont[64][8][2];

class Menu: public Context<Menu>
{
private:
	GLuint m_iVertexArray;
	GLuint m_iFontBuffer;
	GLuint m_iTextBuffer;

	double m_dSpeed = 0;
	std::chrono::steady_clock::time_point m_MenuUpdate;

	int m_iCharCount;
	std::list<Control> m_lstControl;

	float m_fScaleX;
	float m_fScaleY;

	Control* m_pToggle;
	Control* m_pRealSpeed;
	Control* m_pNominalSpeed;

public:
	Menu(Life* pApp);
	~Menu();

	SDL_Window* GetWindow();
	void SetFontScale();
	void UploadTexts();
	bool Tick();
	void HitTest(float fX, float fY);
	const char* GetVertexStart();
	std::size_t GetVertexSize();
	const char* GetGeometryStart();
	std::size_t GetGeometrySize();
	const char* GetFragmentStart();
	std::size_t GetFragmentSize();

private:
	void RefreshTexts();
};
