#pragma once

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>

#include <sstream>
#include <string>

class Control
{
private:
	std::string m_Text;
	int m_iX;
	int m_iY;
	GLfloat m_fScalse;
	GLfloat m_fColor[3];
	void (*m_OnClick)(void*);
	void* m_pArg;

public:
	Control(int iX, int iY, GLfloat scale,
		GLfloat red, GLfloat green, GLfloat blue,
		const char* szText = nullptr,
		void (*OnClick)(void*) = nullptr,
		void* pArg = nullptr);
	~Control();
	void SetText(std::string && str);
	int Write(std::stringstream & stream, float fScaleX, float fScaleY);
	void GetTopLeft(float* pfX, float* pfY, float fScaleX, float fScaleY);
	bool Click(float x, float y, float fScaleX, float fScaleY);
};