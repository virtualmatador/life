#pragma once

#include "context.hpp"

#include <string>
#include <chrono>
#include <vector>

class Game: public Context<Game>
{
private:
	GLuint m_iVertexArray;
	GLuint m_iBuffers[2];

	bool m_bSwap;
	std::chrono::steady_clock::time_point m_GameUpdate;

	int m_iCx;
	int m_iCy;

public:
	Game(Life* pApp);
	~Game();
	
	SDL_Window* GetWindow();
	void SetPointSize();
	bool Load();
	bool Save();
	bool Tick();
	void Edit(float fX, float fY);
	void Upload(std::vector<GLint> vCell);
	std::vector<GLint> Download();
	bool HasData();
	const char* GetVertexStart();
	std::size_t GetVertexSize();
	const char* GetGeometryStart();
	std::size_t GetGeometrySize();
	const char* GetFragmentStart();
	std::size_t GetFragmentSize();

private:
	std::string GetFileName(bool bSave);
};
