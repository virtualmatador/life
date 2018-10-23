#pragma once

#include "context.hpp"

#include <string>

extern const char _binary_src_shader_game_vertex_glsl_end[];
extern const char _binary_src_shader_game_vertex_glsl_start[];

extern const char _binary_src_shader_game_fragment_glsl_end[];
extern const char _binary_src_shader_game_fragment_glsl_start[];

class Game: public Context<Game>
{
private:
	GLuint m_iVertexArray;
	GLuint m_iBuffers[2];
	bool m_bSwap;

	int m_iCx;
	int m_iCy;

public:
	Game(SDL_Window* pWnd);
	~Game();

	void SetPointSize();
	bool Load();
	bool Save();
	void Tick(bool bRun, bool bRasterize);
	const char* GetVertexStart();
	const char* GetVertexEnd();
	const char* GetFragmentStart();
	const char* GetFragmentEnd();

private:
	std::string GetFileName(bool bSave);
};
