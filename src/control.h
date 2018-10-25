#pragma once

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#include <sstream>
#include <string>

class Control
{
private:
	std::string m_Text;
	GLfloat m_fX;
	GLfloat m_fY;
	GLfloat m_fScalse;
	GLfloat m_fColor[3];
	void (*m_OnClick)(void*);
	void* m_pArg;

public:
	Control(GLfloat x, GLfloat y, GLfloat scale,
		GLfloat red = 1.0f,
		GLfloat green = 1.0f,
		GLfloat blue = 1.0f,
		const char* szText = nullptr,
		void (*OnClick)(void*) = nullptr,
		void* pArg = nullptr);
	~Control();
	void SetText(std::string && str);
	int Write(std::stringstream & stream);
	bool Click(float x, float y);
};