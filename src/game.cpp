#include "game.h"

#include "file-dialog.h"

#include <fstream>
#include <vector>

Game::Game(SDL_Window* pWnd)
	: Context<Game>{pWnd}
	, m_iVertexArray{0}
	, m_iBuffers{0, 0}
	, m_bSwap{false}
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
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_iVertexArray);
	glDeleteBuffers(2, m_iBuffers);
}

bool Game::Load()
{
	std::ifstream img(GetFileName(false));
	char sign[3] = {0};
	if (img)
		img >> sign[0] >> sign[1];
	if (strcmp(sign, "P1") != 0)
		return false;
	int iWidth, iHeight;
	if (img)
		img >> iWidth;
	if (img)
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
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iBuffers[0]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, vCell.size() * sizeof(GLint),
		vCell.data(), GL_DYNAMIC_COPY);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_iBuffers[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, vCell.size() * sizeof(GLint),
		nullptr, GL_DYNAMIC_COPY);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	m_bSwap = false;
	m_iCx = iWidth;
	m_iCy = iHeight;
	glUniform1i(glGetUniformLocation(m_iProgram, "width"), m_iCx);
	glUniform1i(glGetUniformLocation(m_iProgram, "height"), m_iCy);
	SetPointSize();
	return true;
}

bool Game::Save()
{
	std::ofstream img(GetFileName(true));
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	return true;
}

std::string Game::GetFileName(bool bSave)
{
	SDL_HideWindow(m_pWnd);
	std::string sName = GetOpenFileName(bSave);
	SDL_ShowWindow(m_pWnd);
	return sName;
}

void Game::SetPointSize()
{
	int iWidth, iHeight;
	SDL_GetWindowSize(m_pWnd, &iWidth, &iHeight);
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	glPointSize(std::min(0.75 * iWidth / m_iCx, 0.75 * iHeight / m_iCy));
}

void Game::Tick(bool bRun, bool bRasterize)
{
	SDL_GL_MakeCurrent(m_pWnd, m_pContext);
	if (bRun)
		m_bSwap = !m_bSwap;
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_bSwap, m_iBuffers[0]);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1 - m_bSwap, m_iBuffers[1]);
	if (bRasterize)
		glDisable(GL_RASTERIZER_DISCARD);
	else
		glEnable(GL_RASTERIZER_DISCARD);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, m_iCx * m_iCy);
	glFinish();
}

const char* Game::GetVertexStart()
{
	return _binary_src_shader_game_vertex_glsl_start;
}

const char* Game::GetVertexEnd()
{
	return _binary_src_shader_game_vertex_glsl_end;
}

const char* Game::GetFragmentStart()
{
	return _binary_src_shader_game_fragment_glsl_start;
}

const char* Game::GetFragmentEnd()
{
	return _binary_src_shader_game_fragment_glsl_end;
}
