#include "menu.h"

#include <sstream>
#include <iomanip>
#include <vector>

const float Menu::m_arFont[][8][2] =
{	
	{ // SPACE
		{-1.0, -1.0}
	}, 
	{ // !
		{0.5, 0.0}, {0.375, 0.25}, {0.625, 0.25}, {0.5, 0.0}, {-1.0, 0.0}, {0.5, 0.5}, {0.5, 1.5}, {-1.0, -1.0}
	}, 
	{ // "
		{0.25, 1.25}, {0.25, 0.75}, {-1.0, 0.0}, {0.75, 1.25}, {0.75, 0.75}, {-1.0, -1.0}
	}, 
	{ // #
		{0.0, 0.5}, {1.0, 0.5}, {0.75, 0.25}, {0.75, 1.25}, {1.0, 1.0}, {0.0, 1.0}, {0.25, 1.25}, {0.25, 0.25}
	}, 
	{ // $
		{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}, {-1.0, 0.0}, {0.5, 0.0}, {0.5, 1.5}, {-1.0, -1.0}
	}, 
	{ // %
		{0.0, 0.0}, {1.0, 1.5}, {-1.0, 0.0}, {0.25, 1.25}, {0.25, 1.0}, {-1.0, 0.0}, {0.75, 0.5}, {0.75, 0.25}
	}, 
	{ // &
		{1.0, 0.0}, {0.5, 1.5}, {1.0, 1.0}, {0.0, 0.5}, {0.5, 0.0}, {1.0, 0.5}, {-1.0, -1.0}
	}, 
	{ // '
		{0.5, 1.25}, {0.5, 0.75}, {-1.0, -1.0}
	}, 
	{ // (
		{0.75, 0.0}, {0.25, 0.5}, {0.25, 1.0}, {0.75, 1.5}, {-1.0, -1.0}
	}, 
	{ // )
		{0.25, 0.0}, {0.75, 0.5}, {0.75, 1.0}, {0.25, 1.5}, {-1.0, -1.0}
	}, 
	{ // *
		{0.0, 0.0}, {0.5, 1.5}, {1.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {0.0, 0.0}, {-1.0, -1.0}
	}, 
	{ // +
		{0.125, 0.75}, {0.875, 0.75}, {-1.0, 0.0}, {0.5, 1.125}, {0.5, 0.375}, {-1.0, -1.0}
	}, 
	{ // ,
		{0.25, 0.0}, {0.5, 0.25}, {-1.0, -1.0}
	}, 
	{ // -
		{0.25, 0.75}, {0.75, 0.75}, {-1.0, -1.0}
	}, 
	{ // .
		{0.375, 0.0}, {0.5, 0.0}, {-1.0, -1.0}
	}, 
	{ // /
		{0.0, 0.0}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // 0
		{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.5}, {0.0, 1.5}, {0.0, 0.0}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // 1
		{0.5, 0.0}, {0.5, 1.5}, {0.375, 1.25}, {-1.0, -1.0}
	}, 
	{ // 2
		{0.0, 1.5}, {1.0, 1.5}, {1.0, 0.875}, {0.0, 0.625}, {0.0, 0.0}, {1.0, 0.0}, {-1.0, -1.0}
	}, 
	{ // 3
		{0.0, 1.5}, {1.0, 1.5}, {1.0, 0.0}, {0.0, 0.0}, {-1.0, 0.0}, {0.0, 0.75}, {1.0, 0.75}, {-1.0, -1.0}
	}, 
	{ // 4
		{0.0, 1.5}, {0.0, 0.75}, {1.0, 0.75}, {-1.0, 0.0}, {1.0, 1.5}, {1.0, 0.0}, {-1.0, -1.0}
	}, 
	{ // 5
		{0.0, 0.0}, {1.0, 0.0}, {1.0, 0.75}, {0.0, 0.875}, {0.0, 1.5}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // 6
		{0.0, 1.5}, {0.0, 0.0}, {1.0, 0.0}, {1.0, 0.625}, {0.0, 0.875}, {-1.0, -1.0}
	}, 
	{ // 7
		{0.0, 1.5}, {1.0, 1.5}, {1.0, 0.75}, {0.5, 0.0}, {-1.0, -1.0}
	}, 
	{ // 8
		{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.5}, {0.0, 1.5}, {0.0, 0.0}, {-1.0, 0.0}, {0.0, 0.75}, {1.0, 0.75}
	}, 
	{ // 9
		{1.0, 0.0}, {1.0, 1.5}, {0.0, 1.5}, {0.0, 0.875}, {1.0, 0.625}, {-1.0, -1.0}
	},
	{ // :
		{0.5, 1.125}, {0.5, 0.875}, {-1.0, 0.0}, {0.5, 0.625}, {0.5, 0.375}, {-1.0, -1.0}
	}, 
	{  // ;
		{0.5, 1.125}, {0.5, 0.875}, {-1.0, 0.0}, {0.5, 0.625}, {0.125, 0.25}, {-1.0, -1.0}
	}, 
	{// <
		{0.75, 0.0}, {0.25, 0.75}, {0.75, 1.5}, {-1.0, -1.0}
	}, 
	{ // =
		{0.125, 0.5}, {0.875, 0.5}, {-1.0, 0.0}, {0.125, 1.0}, {0.875, 1.0}, {-1.0, -1.0}
	}, 
	{ // >
		{0.25, 0.0}, {0.75, 0.75}, {0.25, 1.5}, {-1.0, -1.0}
	}, 
	{ // ? 
		{0.0, 1.0}, {0.5, 1.5}, {1.0, 1.0}, {0.5, 0.5}, {-1.0, 0.0}, {0.5, 0.125}, {0.5, 0.0}, {-1.0, -1.0}
	}, 
	{ // e
		{1.0, 0.5}, {0.5, 0.0}, {0.0, 0.5}, {0.0, 1.0}, {0.5, 1.5}, {1.0, 1.0}, {0.5, 0.5}, {0.375, 0.75}
	}, 
	{ // A
		{0.0, 0.0}, {0.0, 1.0}, {0.5, 1.5}, {1.0, 1.0}, {1.0, 0.0}, {-1.0, 0.0}, {0.0, 0.5}, {1.0, 0.5}
	}, 
	{ // B
		{0.0, 0.0}, {0.0, 1.5}, {0.5, 1.5}, {1.0, 1.25}, {0.5, 0.75}, {1.0, 0.25}, {0.5, 0.0}, {0.0, 0.0}
	}, 
	{ // C
		{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // D
		{0.0, 0.0}, {0.0, 1.5}, {0.5, 1.5}, {1.0, 1.0}, {1.0, 0.5}, {0.5, 0.0}, {0.0, 0.0}, {-1.0, -1.0}
	}, 
	{ // E
		{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}, {-1.0, 0.0}, {0.0, 0.75}, {0.75, 0.75}, {-1.0, -1.0}
	}, 
	{ // F
		{0.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}, {-1.0, 0.0}, {0.0, 0.75}, {0.75, 0.75}, {-1.0, -1.0}
	}, 
	{ // G
		{0.75, 0.75}, {1.0, 0.5}, {1.0, 0.0}, {0.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // H
		{0.0, 0.0}, {0.0, 1.5}, {-1.0, 0.0}, {0.0, 0.75}, {1.0, 0.75}, {-1.0, 0.0}, {1.0, 1.5}, {1.0, 0.0}
	}, 
	{ // I
		{0.0, 0.0}, {1.0, 0.0}, {-1.0, 0.0}, {0.5, 0.0}, {0.5, 1.5}, {-1.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}
	}, 
	{ // J
		{0.0, 0.5}, {0.5, 0.0}, {1.0, 0.0}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // K
		{0.0, 0.0}, {0.0, 1.5}, {-1.0, 0.0}, {1.0, 1.5}, {0.0, 0.75}, {0.75, 0.0}, {-1.0, -1.0}
	}, 
	{ // L
		{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // M
		{0.0, 0.0}, {0.0, 1.5}, {0.5, 1.0}, {1.0, 1.5}, {1.0, 0.0}, {-1.0, -1.0}
	}, 
	{ // N
		{0.0, 0.0}, {0.0, 1.5}, {1.0, 0.0}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // O
		{0.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}, {1.0, 0.0}, {0.0, 0.0}, {-1.0, -1.0}
	}, 
	{ // P
		{0.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}, {1.0, 0.75}, {0.0, 0.625}, {-1.0, -1.0}
	}, 
	{ // Q
		{0.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}, {1.0, 0.5}, {0.0, 0.0}, {-1.0, 0.0}, {0.5, 0.5}, {1.0, 0.0}
	}, 
	{ // R
		{0.0, 0.0}, {0.0, 1.5}, {1.0, 1.5}, {1.0, 0.75}, {0.0, 0.625}, {-1.0, 0.0}, {0.5, 0.625}, {1.0, 0.0}
	}, 
	{ // S
		{0.0, 0.25}, {0.25, 0.0}, {1.0, 0.0}, {1.0, 0.625}, {0.0, 0.875}, {0.0, 1.5}, {0.75, 1.5}, {1.0, 1.25}
	}, 
	{ // T
		{0.0, 1.5}, {1.0, 1.5}, {-1.0, 0.0}, {0.5, 1.5}, {0.5, 0.0}, {-1.0, -1.0}
	}, 
	{ // U
		{0.0, 1.5}, {0.0, 0.25}, {0.5, 0.0}, {1.0, 0.25}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // V
		{0.0, 1.5}, {0.5, 0.0}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // W
		{0.0, 1.5}, {0.25, 0.0}, {0.5, 0.5}, {0.75, 0.0}, {1.0, 1.5}, {-1.0, -1.0}
	}, 
	{ // X
		{0.0, 0.0}, {1.0, 1.5}, {-1.0, 0.0}, {0.0, 1.5}, {1.0, 0.0}, {-1.0, -1.0}
	}, 
	{ // Y
		{0.0, 1.5}, {0.5, 0.75}, {1.0, 1.5}, {-1.0, 0.0}, {0.5, 0.75}, {0.5, 0.0}, {-1.0, -1.0}
	}, 
	{ // Z
		{0.0, 1.5}, {1.0, 1.5}, {0.0, 0.0}, {1.0, 0.0}, {-1.0, 0.0}, {0.25, 0.75}, {0.75, 0.75}, {-1.0, -1.0}
	},
	{ // [
		{0.75, 0.0}, {0.25, 0.0}, {0.25, 1.5}, {0.75, 1.5}, {-1.0, -1.0}
	}, 
	{ // \
		{0.0, 1.5}, {1.0, 0.0}, {-1.0, -1.0}
	}, 
	{ // ]
		{0.25, 0.0}, {0.75, 0.0}, {0.75, 1.5}, {0.25, 1.5}, {-1.0, -1.0}
	}, 
	{ // ^
		{0.25, 0.75}, {0.5, 1.5}, {0.75, 0.75}, {-1.0, -1.0}
	}, 
	{ // _
		{0.0, 0.0}, {1.0, 0.0}, {-1.0, -1.0}
	},
};

Menu::Menu(SDL_Window* pWnd)
	: Context<Menu>{pWnd}
	, m_iFontBuffer{0}
	, m_iTextBuffer{0}
	, m_iCharCount{0}
	, m_Speed{"", -0.9, 0.9, 0.05, {1.0, 1.0, 1.0}}
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
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_iFontBuffer);
	glGenBuffers(1, &m_iTextBuffer);
	if (m_iTextBuffer == 0)
		throw "glGenBuffers";
	glLineWidth(2);
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
	m_iCharCount = 0;
	std::stringstream arData(std::ios::in | std::ios::out | std::ios::binary);
	UploadText(m_Speed, arData);
	arData.seekg(0, std::ios::beg);
	std::vector<unsigned char> vData(m_iCharCount * 7 * sizeof(GLfloat));
	arData.read((char*)vData.data(), vData.size());
	glBindBuffer(GL_ARRAY_BUFFER, m_iTextBuffer);
	glBufferData(GL_ARRAY_BUFFER, vData.size(),
		vData.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	int stride = 6 * sizeof(GLfloat) + sizeof(GLint);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(GLfloat)));
	glVertexAttribIPointer(2, 1, GL_INT, stride, (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat) + sizeof(GLint)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Menu::UploadText(TEXT & txt, std::stringstream & stream)
{
	for (int i = 0; i < txt.text.size(); ++i)
	{
		float fData = txt.fX + txt.fScalse * i;
		stream.write((char*)&fData, sizeof(GLfloat));
		stream.write((char*)&txt.fY, sizeof(GLfloat));
		fData = txt.fScalse * 0.7;
		stream.write((char*)&fData, sizeof(GLfloat));
		int iData = txt.text[i] - 32;
		stream.write((char*)&iData, sizeof(GLint));
		stream.write((char*)txt.fColor, sizeof(GLfloat) * 3);
	}
	m_iCharCount += txt.text.size();
}

void Menu::Tick(bool bUpdate, int64_t iRealSpeed, int64_t iNominalSpeed)
{
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	if (bUpdate)
	{
		std::stringstream ss;
		ss << "SPEED: " << std::setw(7) << iRealSpeed << " EXPECT: " << std::setw(10) << iNominalSpeed;
		m_Speed.text = ss.str();
		UploadTexts();
	}
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
