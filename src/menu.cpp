#include <sstream>
#include <iomanip>
#include <vector>

#include <resources.h>

#include "life.h"

#include "menu.h"

Menu::Menu(Life* pApp)
	: Context<Menu>{pApp}
	, m_iFontBuffer{0}
	, m_iTextBuffer{0}
	, m_iCharCount{0}
	, m_MenuUpdate{std::chrono::nanoseconds(0)}
	, m_dSpeed{0.0}
	, m_fScaleX{0}
	, m_fScaleY{0}
{
	glGenVertexArrays(1, &m_iVertexArray);
	if (m_iVertexArray == 0)
		throw "glGenVertexArrays";
	glBindVertexArray(m_iVertexArray);
	glGenBuffers(1, &m_iFontBuffer);
	if (m_iFontBuffer == 0)
		throw "glGenBuffers";
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iFontBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(arFont),
		arFont, GL_STATIC_COPY);
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
	int stride = 7 * sizeof(GLfloat) + sizeof(GLint);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(GLfloat)));
	glVertexAttribIPointer(2, 1, GL_INT, stride, (void*)(4 * sizeof(GLfloat)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(4 * sizeof(GLfloat) + sizeof(GLint)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_lstControl.insert(m_lstControl.end(),{0, 0, 1.0, 1.0, 1.0, 1.0, "LOAD", [](void* pArg)
	{
		((Life*)pArg)->Load();
	}, (void*)m_pApp});
	m_lstControl.insert(m_lstControl.end(),{0, 1, 1.0, 1.0, 1.0, 1.0, "SAVE", [](void* pArg)
	{
		((Life*)pArg)->Save();
	}, (void*)m_pApp});
	m_pToggle = &*m_lstControl.insert(m_lstControl.end(),{6, 0, 1.0, 1.0, 1.0, 1.0, "PLAY", [](void* pArg)
	{
		((Life*)pArg)->ToggleGame();
	}, (void*)m_pApp});
	m_lstControl.insert(m_lstControl.end(),{6, 1, 1.0, 1.0, 1.0, 1.0, "STEP", [](void* pArg)
	{
		((Life*)pArg)->Frame();
	}, (void*)m_pApp});
	m_lstControl.insert(m_lstControl.end(),{12, 0, 1.0, 1.0, 1.0, 1.0, "EDIT", [](void* pArg)
	{
		((Life*)pArg)->ToggleEdit();
	}, (void*)m_pApp});
	m_lstControl.insert(m_lstControl.end(),{12, 1, 1.0, 1.0, 1.0, 1.0, "HIDE", [](void* pArg)
	{
		((Life*)pArg)->ToggleMenu();
	}, (void*)m_pApp});
	m_lstControl.insert(m_lstControl.end(),{18, 0, 1.0, 1.0, 1.0, 1.0, "FAST", [](void* pArg)
	{
		((Life*)pArg)->SpeedUp();
	}, (void*)m_pApp});
	m_lstControl.insert(m_lstControl.end(),{18, 1, 1.0, 1.0, 1.0, 1.0, "SLOW", [](void* pArg)
	{
		((Life*)pArg)->SpeedDown();
	}, (void*)m_pApp});
	m_lstControl.insert(m_lstControl.end(),{24, 0, 1.0, 0.75, 0.75, 0.75, "REAL:", [](void* pArg)
	{
		((Life*)pArg)->SpeedUp();
	}, (void*)m_pApp});
	m_lstControl.insert(m_lstControl.end(),{24, 1, 1.0, 0.75, 0.75, 0.75, "GOAL:", [](void* pArg)
	{
		((Life*)pArg)->SpeedDown();
	}, (void*)m_pApp});
	m_pRealSpeed = &*m_lstControl.insert(m_lstControl.end(), {30, 0, 1.0, 0.75, 0.75, 0.75});
	m_pNominalSpeed = &*m_lstControl.insert(m_lstControl.end(),{30, 1, 1.0, 0.75, 0.75, 0.75});
	m_lstControl.insert(m_lstControl.end(),{41, 0, 0.75, 0.5, 0.5, 1.0, "WWW.SHAIDIN.COM"});
	m_lstControl.insert(m_lstControl.end(),{41, 1, 0.75, 0.5, 0.5, 1.0, "ALI ASADPOOR"});
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

void Menu::SetFontScale()
{
	float fFontX, fFontY;
	m_pApp->GetFontSize(&fFontX, &fFontY);
	m_fScaleX = fFontX * 2.0f / m_pApp->m_ptClient.x;
	m_fScaleY = fFontY * 2.0f / m_pApp->m_ptClient.y;
	SDL_GL_MakeCurrent(m_pApp->m_pWnd, m_pContext);
	glLineWidth(std::min(fFontX, fFontY) / 8);
}

void Menu::UploadTexts()
{
	RefreshTexts();
	m_iCharCount = 0;
	std::stringstream arData(std::ios::in | std::ios::out | std::ios::binary);
	for (auto & cnt : m_lstControl)
		m_iCharCount += cnt.Write(arData, m_fScaleX, m_fScaleY);
	arData.seekg(0, std::ios::beg);
	std::vector<unsigned char> vData(m_iCharCount * (7 * sizeof(GLfloat) + sizeof(GLint)));
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
		ss << (m_pApp->m_bRun && !m_pApp->m_bFrame ? "STOP" : "PLAY");
		m_pToggle->SetText(ss.str());
	}
	{
		std::stringstream ss;
		ss << m_dSpeed;
		m_pRealSpeed->SetText(ss.str());
	}
	{
		std::stringstream ss;
		ss << (m_pApp->m_iDelay > 0ll ? double(1000.0 * 1000.0) / m_pApp->m_iDelay : (10.0 * 1000.0 * 1000.0));
		m_pNominalSpeed->SetText(ss.str());
	}
}
bool Menu::Tick()
{
	int64_t duration = (m_pApp->m_frameTime - m_MenuUpdate).count() / 1000ll;
	bool bUpdate = m_pApp->m_bRefresh || duration > (500ll * 1000ll);
	if (!m_pApp->m_bRefresh && m_pApp->m_bRun && bUpdate)
	{
		m_MenuUpdate = m_pApp->m_frameTime;
		m_dSpeed = m_pApp->m_FrameCount == 0 ? 0 : double(m_pApp->m_FrameCount) * (1000.0 * 1000.0) / duration;
		m_pApp->m_FrameCount = 0;
	}
	SDL_GL_MakeCurrent(m_pApp->m_pWnd, m_pContext);
	if (bUpdate)
		UploadTexts();
	if (m_pApp->m_bMenu)
		glDrawArrays(GL_POINTS, 0, m_iCharCount);
	glFinish();
	return bUpdate;
}

void Menu::HitTest(float fX, float fY)
{
	for (auto & cnt : m_lstControl)
		if (cnt.Click(fX, fY, m_fScaleX, m_fScaleY))
			break;
}

const char* Menu::GetVertexStart()
{
	return (const char*)menu_vertex_glsl;
}

std::size_t Menu::GetVertexSize()
{
	return menu_vertex_glsl_size;
}

const char* Menu::GetGeometryStart()
{
	return (const char*)menu_geometry_glsl;
}

std::size_t Menu::GetGeometrySize()
{
	return menu_geometry_glsl_size;
}

const char* Menu::GetFragmentStart()
{
	return (const char*)menu_fragment_glsl;
}

std::size_t Menu::GetFragmentSize()
{
	return menu_fragment_glsl_size;
}
