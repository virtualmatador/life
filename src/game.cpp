#include <cstring>
#include <fstream>
#include <vector>

#include "file-dialog.h"
#include "life.h"

#include "game.h"

Game::Game(Life* pApp)
	: Context<Game>{pApp}
	, m_iVertexArray{0}
	, m_iBuffers{0, 0}
	, m_bSwap{false}
	, m_GameUpdate{std::chrono::nanoseconds(0)}
	, m_iCx{0}
	, m_iCy{0}
{
	glDisable(GL_PROGRAM_POINT_SIZE);
	glGenVertexArrays(1, &m_iVertexArray);
	if (m_iVertexArray == 0)
		throw "glGenVertexArrays";
	glBindVertexArray(m_iVertexArray);
	glGenBuffers(2, m_iBuffers);
	if (m_iBuffers[0] == 0 || m_iBuffers[1] == 0)
		throw "glGenBuffers";
}	

Game::~Game()
{
	SDL_GL_MakeCurrent(m_pApp->m_pWnd, m_pContext);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_iVertexArray);
	glDeleteBuffers(2, m_iBuffers);
}

SDL_Window* Game::GetWindow()
{
	return m_pApp->m_pWnd;
}

bool Game::Load()
{
	std::ifstream img(GetFileName(false));
	char sign[3] = {0};
	if (!img)
		return false;
	img >> sign[0] >> sign[1];
	if (std::strcmp(sign, "P1") != 0)
		return false;
	int iWidth, iHeight;
	if (!img)
		return false;
	img >> iWidth;
	if (!img)
		return false;
	img >> iHeight;
	if (iWidth <= 0 || iWidth > 0x1000 || iHeight <= 0 || iHeight > 0x1000)
		return false;
	std::vector<GLint> vCell(iWidth * iHeight);
	for (int y = 0; y < iHeight; ++y)
	{
		for (int x = 0; x < iWidth; ++x)
		{
			if (!img)
				return false;
			img >> vCell[y * iWidth + x];
		}
	}
	m_bSwap = false;
	m_iCx = iWidth;
	m_iCy = iHeight;
	Upload(vCell);
	glUniform1i(glGetUniformLocation(m_iProgram, "width"), m_iCx);
	glUniform1i(glGetUniformLocation(m_iProgram, "height"), m_iCy);
	SetPointSize();
	return true;
}

bool Game::Save()
{
	if (m_iCx <= 0 || m_iCy <= 0)
		return false;
	std::ofstream img(GetFileName(true));
	if (!img)
		return false;
	std::vector<GLint> vCell = Download();
	if (!img)
		return false;
	img << "P1" << std::endl;
	if (!img)
		return false;
	img << m_iCx << " " << m_iCy << std::endl;
	for (int y = 0; y < m_iCy; ++y)
	{
		for (int x = 0; x < m_iCx; ++x)
		{
			if (!img)
				return false;
			img << vCell[y * m_iCx + x] << " ";
		}
		img << std::endl;
	}
	return true;
}

std::string Game::GetFileName(bool bSave)
{
	SDL_HideWindow(m_pApp->m_pWnd);
	std::string sName = ShowFileDialog(bSave);
	SDL_ShowWindow(m_pApp->m_pWnd);
	return sName;
}

void Game::SetPointSize()
{
	SDL_GL_MakeCurrent(m_pApp->m_pWnd, m_pContext);
	glPointSize(std::min(0.8 * m_pApp->m_ptClient.x / m_iCx, 0.8 * m_pApp->m_ptClient.y / m_iCy));
}

bool Game::Tick()
{
	int64_t duration = (m_pApp->m_frameTime - m_GameUpdate).count() / 1000ll;
	bool bUpdate = m_pApp->m_bRefresh || duration > (50ll * 1000ll);
	if (!m_pApp->m_bRefresh && m_pApp->m_bRun)
	{
		m_bSwap = !m_bSwap;
		++m_pApp->m_FrameCount;
	}
	SDL_GL_MakeCurrent(m_pApp->m_pWnd, m_pContext);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bSwap, m_iBuffers[0]);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1 - m_bSwap, m_iBuffers[1]);
	if (bUpdate)
	{
		if (!m_pApp->m_bRefresh)
			m_GameUpdate = m_pApp->m_frameTime;
		glDisable(GL_RASTERIZER_DISCARD);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else
		glEnable(GL_RASTERIZER_DISCARD);
	glDrawArrays(GL_POINTS, 0, m_iCx * m_iCy);
	glFinish();
	return bUpdate;
}

void Game::Edit(float fX, float fY)
{
	if (m_iCx > 0 && m_iCy > 0)
	{
		int iX = (fX + 1.0) / 2.0 * m_iCx;
		int iY = (1.0 - fY) / 2.0 * m_iCy;
		std::vector<GLint> vCell = Download();
		vCell[iY * m_iCx + iX] = !vCell[iY * m_iCx + iX];
		Upload(vCell);
	}
}

void Game::Upload(std::vector<GLint> vCell)
{
	SDL_GL_MakeCurrent(m_pApp->m_pWnd, m_pContext);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iBuffers[m_bSwap]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, vCell.size() * sizeof(GLint),
		vCell.data(), GL_DYNAMIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iBuffers[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, vCell.size() * sizeof(GLint),
		nullptr, GL_DYNAMIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

std::vector<GLint> Game::Download()
{
	std::vector<GLint> vCell(m_iCx * m_iCy);
	SDL_GL_MakeCurrent(m_pApp->m_pWnd, m_pContext);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iBuffers[m_bSwap]);
	glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, vCell.size() * sizeof(GLint), vCell.data());
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	return vCell;
}

bool Game::HasData()
{
	return m_iCx > 0 && m_iCy > 0;
}

const char* Game::GetVertexStart()
{
	return _binary_game_vertex_glsl_start;
}

const char* Game::GetVertexEnd()
{
	return _binary_game_vertex_glsl_end;
}

const char* Game::GetGeometryStart()
{
	return _binary_game_geometry_glsl_start;
}

const char* Game::GetGeometryEnd()
{
	return _binary_game_geometry_glsl_end;
}

const char* Game::GetFragmentStart()
{
	return _binary_game_fragment_glsl_start;
}

const char* Game::GetFragmentEnd()
{
	return _binary_game_fragment_glsl_end;
}
