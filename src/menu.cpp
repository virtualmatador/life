#include "menu.h"

#include <sstream>
#include <vector>

const int Menu::m_arFont[][8][2] =
{    
    {
		{0, 0}, {8, 0}, {8, 12}, {0, 12}, {0, 0}, {8, 12}, {15, 15}
	}, 
    {
		{4, 0}, {4, 12}, {3, 10}, {15, 15}
	}, 
    {
		{0, 12}, {8, 12}, {8, 7}, {0, 5}, {0, 0}, {8, 0}, {15, 15}
	}, 
    {
		{0, 12}, {8, 12}, {8, 0}, {0, 0}, {15, 14}, {0, 6}, {8, 6}, {15, 15}
	}, 
    {
		{0, 12}, {0, 6}, {8, 6}, {15, 14}, {8, 12}, {8, 0}, {15, 15}
	}, 
    {
		{0, 0}, {8, 0}, {8, 6}, {0, 7}, {0, 12}, {8, 12}, {15, 15}
	}, 
    {
		{0, 12}, {0, 0}, {8, 0}, {8, 5}, {0, 7}, {15, 15}
	}, 
    {
		{0, 12}, {8, 12}, {8, 6}, {4, 0}, {15, 15}
	}, 
    {
		{0, 0}, {8, 0}, {8, 12}, {0, 12}, {0, 0}, {15, 14}, {0, 6}, {8, 6}
	}, 
    {
		{8, 0}, {8, 12}, {0, 12}, {0, 7}, {8, 5}, {15, 15}
	}, 
    {
		{15, 15}
	}, 
    {
		{3, 0}, {4, 0}, {15, 15}
	}, 
    {
		{2, 0}, {4, 2}, {15, 15}
	}, 
    {
		{2, 6}, {6, 6}, {15, 15}
	}, 
    {
		{1, 6}, {7, 6}, {15, 14}, {4, 9}, {4, 3}, {15, 15}
	}, 
    {
		{4, 0}, {3, 2}, {5, 2}, {4, 0}, {15, 14}, {4, 4}, {4, 12}, {15, 15}
	}, 
    {
		{0, 4}, {8, 4}, {6, 2}, {6, 10}, {8, 8}, {0, 8}, {2, 10}, {2, 2}
	}, 
    {
		{2, 6}, {4, 12}, {6, 6}, {15, 15}
	}, 
    {
		{1, 4}, {7, 4}, {15, 14}, {1, 8}, {7, 8}, {15, 15}
	}, 
    {
		{0, 0}, {4, 12}, {8, 0}, {0, 8}, {8, 8}, {0, 0}, {15, 15}
	}, 
    {
		{0, 0}, {8, 0}, {15, 15}
	}, 
    {
		{0, 0}, {8, 12}, {15, 15}
	}, 
    {
		{0, 12}, {8, 0}, {15, 15}
	}, 
    {
		{8, 4}, {4, 0}, {0, 4}, {0, 8}, {4, 12}, {8, 8}, {4, 4}, {3, 6}
	}, 
    {
		{6, 2}, {2, 6}, {6, 10}, {15, 14}, {4, 12}, {4, 0}, {15, 15}
	}, 
    {
		{8, 0}, {4, 12}, {8, 8}, {0, 4}, {4, 0}, {8, 4}, {15, 15}
	}, 
    {
		{6, 0}, {2, 0}, {2, 12}, {6, 12}, {15, 15}
	}, 
    {
		{2, 0}, {6, 0}, {6, 12}, {2, 12}, {15, 15}
	}, 
    {
		{6, 0}, {2, 4}, {2, 8}, {6, 12}, {15, 15}
	}, 
    {
		{2, 0}, {6, 4}, {6, 8}, {2, 12}, {15, 15}
	}, 
    {
		{6, 0}, {4, 2}, {4, 10}, {6, 12}, {15, 14}, {2, 6}, {4, 6}, {15, 15}
	}, 
    {
		{4, 0}, {6, 2}, {6, 10}, {4, 12}, {15, 14}, {6, 6}, {8, 6}, {15, 15}
	}, 
    {
		{0, 0}, {8, 12}, {15, 14}, {2, 10}, {2, 8}, {15, 14}, {6, 4}, {6, 2}
	}, 
    {
		{6, 0}, {2, 6}, {6, 12}, {15, 15}
	}, 
    {
		{2, 0}, {6, 6}, {2, 12}, {15, 15}
	}, 
    {
		{4, 0}, {4, 5}, {15, 14}, {4, 6}, {4, 12}, {15, 15}
	}, 
    {
		{4, 9}, {4, 7}, {15, 14}, {4, 5}, {4, 3}, {15, 15}
	}, 
    {
		{4, 9}, {4, 7}, {15, 14}, {4, 5}, {1, 2}, {15, 15}
	}, 
    {
		{2, 10}, {2, 6}, {15, 14}, {6, 10}, {6, 6}, {15, 15}
	}, 
    {
		{2, 6}, {6, 10}, {15, 15}
	}, 
    {
		{2, 10}, {6, 6}, {15, 15}
	}, 
    {
		{0, 4}, {2, 8}, {6, 4}, {8, 8}, {15, 15}
	}, 
    {
		{0, 8}, {4, 12}, {8, 8}, {4, 4}, {15, 14}, {4, 1}, {4, 0}, {15, 15}
	}, 
    {
		{0, 0}, {0, 8}, {4, 12}, {8, 8}, {8, 0}, {15, 14}, {0, 4}, {8, 4}
	}, 
    {
		{0, 0}, {0, 12}, {4, 12}, {8, 10}, {4, 6}, {8, 2}, {4, 0}, {0, 0}
	}, 
    {
		{8, 0}, {0, 0}, {0, 12}, {8, 12}, {15, 15}
	}, 
    {
		{0, 0}, {0, 12}, {4, 12}, {8, 8}, {8, 4}, {4, 0}, {0, 0}, {15, 15}
	}, 
    {
		{8, 0}, {0, 0}, {0, 12}, {8, 12}, {15, 14}, {0, 6}, {6, 6}, {15, 15}
	}, 
    {
		{0, 0}, {0, 12}, {8, 12}, {15, 14}, {0, 6}, {6, 6}, {15, 15}
	}, 
    {
		{6, 6}, {8, 4}, {8, 0}, {0, 0}, {0, 12}, {8, 12}, {15, 15}
	}, 
    {
		{0, 0}, {0, 12}, {15, 14}, {0, 6}, {8, 6}, {15, 14}, {8, 12}, {8, 0}
	}, 
    {
		{0, 0}, {8, 0}, {15, 14}, {4, 0}, {4, 12}, {15, 14}, {0, 12}, {8, 12}
	}, 
    {
		{0, 4}, {4, 0}, {8, 0}, {8, 12}, {15, 15}
	}, 
    {
		{0, 0}, {0, 12}, {15, 14}, {8, 12}, {0, 6}, {6, 0}, {15, 15}
	}, 
    {
		{8, 0}, {0, 0}, {0, 12}, {15, 15}
	}, 
    {
		{0, 0}, {0, 12}, {4, 8}, {8, 12}, {8, 0}, {15, 15}
	}, 
    {
		{0, 0}, {0, 12}, {8, 0}, {8, 12}, {15, 15}
	}, 
    {
		{0, 0}, {0, 12}, {8, 12}, {8, 0}, {0, 0}, {15, 15}
	}, 
    {
		{0, 0}, {0, 12}, {8, 12}, {8, 6}, {0, 5}, {15, 15}
	}, 
    {
		{0, 0}, {0, 12}, {8, 12}, {8, 4}, {0, 0}, {15, 14}, {4, 4}, {8, 0}
	}, 
    {
		{0, 0}, {0, 12}, {8, 12}, {8, 6}, {0, 5}, {15, 14}, {4, 5}, {8, 0}
	}, 
    {
		{0, 2}, {2, 0}, {8, 0}, {8, 5}, {0, 7}, {0, 12}, {6, 12}, {8, 10}
	}, 
    {
		{0, 12}, {8, 12}, {15, 14}, {4, 12}, {4, 0}, {15, 15}
	}, 
    {
		{0, 12}, {0, 2}, {4, 0}, {8, 2}, {8, 12}, {15, 15}
	}, 
    {
		{0, 12}, {4, 0}, {8, 12}, {15, 15}
	}, 
    {
		{0, 12}, {2, 0}, {4, 4}, {6, 0}, {8, 12}, {15, 15}
	}, 
    {
		{0, 0}, {8, 12}, {15, 14}, {0, 12}, {8, 0}, {15, 15}
	}, 
    {
		{0, 12}, {4, 6}, {8, 12}, {15, 14}, {4, 6}, {4, 0}, {15, 15}
	}, 
    {
		{0, 12}, {8, 12}, {0, 0}, {8, 0}, {15, 14}, {2, 6}, {6, 6}, {15, 15}
	}
};

Menu::Menu(SDL_Window* pWnd)
	: Context<Menu>{pWnd}
	, m_iFontBuffer{0}
	, m_iTextBuffer{0}
	, m_iCharCount{0}
	, m_Speed{"Hello", 0, 0, 0.05, {1.0, 0, 0}}
{
	glGenVertexArrays(1, &m_iVertexArray);
	if (m_iVertexArray == 0)
		throw "glGenVertexArrays";
	glBindVertexArray(m_iVertexArray);
	glGenBuffers(1, &m_iFontBuffer);
	if (m_iFontBuffer == 0)
		throw "glGenBuffers";
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iFontBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Menu::m_arFont),
		Menu::m_arFont, GL_STATIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	glGenBuffers(1, &m_iTextBuffer);
	if (m_iTextBuffer == 0)
		throw "glGenBuffers";
	UploadTexts();
}

Menu::~Menu()
{
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_iVertexArray);
	glDeleteBuffers(1, &m_iFontBuffer);
	glDeleteBuffers(1, &m_iTextBuffer);
}

void Menu::UploadTexts()
{
	std::stringstream arData(std::ios::in | std::ios::out | std::ios::binary);
	UploadText(m_Speed, arData);
	arData.seekg(0, std::ios::beg);
	std::vector<unsigned char> vData(m_iCharCount * 6 * sizeof(GLfloat));
	arData.read((char*)vData.data(), vData.size());
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	glBindBuffer(GL_ARRAY_BUFFER, m_iTextBuffer);
	glBufferData(GL_ARRAY_BUFFER, vData.size(),
		vData.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	int stride = 5 * sizeof(GLfloat) + sizeof(GLint);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glVertexAttribIPointer(1, 1, GL_INT, stride, (void*)(2 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(GLfloat) + sizeof(GLint)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Menu::UploadText(TEXT & txt, std::stringstream & stream)
{
	for (int i = 0; i < txt.text.size(); ++i)
	{
		float fData = txt.fX + i * txt.fScalse;
		stream.write((char*)&fData, sizeof(GLfloat));
		stream.write((char*)&txt.fY, sizeof(GLfloat));
		int iData = txt.text[i];
		stream.write((char*)&iData, sizeof(GLint));
		stream.write((char*)txt.fColor, sizeof(GLfloat) * 3);
	}
	m_iCharCount += txt.text.size();
}

void Menu::Tick(int64_t iRealSpeed, int64_t iNominalSpeed)
{
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	glDrawArrays(GL_POINTS, 0, m_iCharCount);
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

const char* Menu::GetGeometryStart()
{
	return _binary_src_shader_menu_geometry_glsl_start;
}

const char* Menu::GetGeometryEnd()
{
	return _binary_src_shader_menu_geometry_glsl_end;
}

const char* Menu::GetFragmentStart()
{
	return _binary_src_shader_menu_fragment_glsl_start;
}

const char* Menu::GetFragmentEnd()
{
	return _binary_src_shader_menu_fragment_glsl_end;
}
