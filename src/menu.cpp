#include "menu.h"
#include "main.h"

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

Menu::Menu(Life* pApp)
	: Context<Menu>{pApp}
	, m_iFontBuffer{0}
	, m_iTextBuffer{0}
	, m_iCharCount{0}
	, m_MenuUpdate{std::chrono::nanoseconds(0)}
	, m_dSpeed{0.0}
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
	glBindBuffer(GL_ARRAY_BUFFER, m_iTextBuffer);
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

	glLineWidth(2);

	m_pRealSpeed = m_lstControl.insert(m_lstControl.end(), {-0.8, -0.7, 0.04})->GetText();
	m_pNominalSpeed = m_lstControl.insert(m_lstControl.end(),{-0.84, -0.78, 0.04})->GetText();
	m_lstControl.insert(m_lstControl.end(),{-0.22, -0.7, 0.03, 0.8, 0.2, 0.2, "UP", [](void* pArg)
	{
		((Life*)pArg)->SpeedUp();
	}, (void*)m_pApp});
	m_lstControl.insert(m_lstControl.end(),{-0.26, -0.84, 0.03, 0.2, 8.0, 0.2, "DOWN", [](void* pArg)
	{
		((Life*)pArg)->SpeedDown();
	}, (void*)m_pApp});
}

Menu::~Menu()
{
	SDL_GL_MakeCurrent(m_pApp->m_pWnd, m_pContext);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_iVertexArray);
	glDeleteBuffers(1, &m_iFontBuffer);
	glDeleteBuffers(1, &m_iTextBuffer);
}

SDL_Window* Menu::GetWindow()
{
	return m_pApp->m_pWnd;
}

void Menu::UploadTexts()
{
	RefreshTexts();
	m_iCharCount = 0;
	std::stringstream arData(std::ios::in | std::ios::out | std::ios::binary);
	for (auto & cnt : m_lstControl)
		m_iCharCount += cnt.Write(arData);
	arData.seekg(0, std::ios::beg);
	std::vector<unsigned char> vData(m_iCharCount * (6 * sizeof(GLfloat) + sizeof(GLint)));
	arData.read((char*)vData.data(), vData.size());
	glBindBuffer(GL_ARRAY_BUFFER, m_iTextBuffer);
	glBufferData(GL_ARRAY_BUFFER, vData.size(),
		vData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Menu::RefreshTexts()
{
	{
		std::stringstream ss;
		ss << "SPEED:" << m_dSpeed;
		*m_pRealSpeed = ss.str();
	}
	{
		std::stringstream ss;
		ss << "EXPECT:" << (m_pApp->m_iDelay > 0ll ? double(1000.0 * 1000.0) / m_pApp->m_iDelay : 0ll);
		*m_pNominalSpeed = ss.str();
	}
}
bool Menu::Tick()
{
	int64_t duration = (m_pApp->m_frameTime - m_MenuUpdate).count() / 1000ll;
	bool bUpdate = !m_pApp->m_bRun || duration > (500ll * 1000ll);
	if (bUpdate && m_pApp->m_bRun)
	{
		m_MenuUpdate = m_pApp->m_frameTime;
		m_dSpeed = m_pApp->m_FrameCount == 0 ? 0 : double(m_pApp->m_FrameCount) * (1000.0 * 1000.0) / duration;
		m_pApp->m_FrameCount = 0;
	}
	SDL_GL_MakeCurrent(m_pApp->m_pWnd, m_pContext);
	if (bUpdate)
		UploadTexts();
	glDrawArrays(GL_POINTS, 0, m_iCharCount);
	glFinish();
}

bool Menu::HitTest(int x, int y)
{
	bool bResult = false;
	int iWidth, iHeight;
	SDL_GetWindowSize(m_pApp->m_pWnd, &iWidth, & iHeight);	
	float fX = float(x * 2) / float(iWidth) - 1;
	float fY = float(y * 2) / float(iHeight) - 1;
	for (auto & cnt : m_lstControl)
	{
		if (cnt.Click(fX, -fY))
			bResult = true;
	}
	return bResult;
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
