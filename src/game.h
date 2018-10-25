#pragma once

#include "context.hpp"

#include <string>
#include <chrono>

extern const char _binary_src_shader_game_vertex_glsl_end[];
extern const char _binary_src_shader_game_vertex_glsl_start[];

extern const char _binary_src_shader_game_geometry_glsl_end[];
extern const char _binary_src_shader_game_geometry_glsl_start[];

extern const char _binary_src_shader_game_fragment_glsl_end[];
extern const char _binary_src_shader_game_fragment_glsl_start[];

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
	const char* GetVertexStart();
	const char* GetVertexEnd();
	const char* GetGeometryStart();
	const char* GetGeometryEnd();
	const char* GetFragmentStart();
	const char* GetFragmentEnd();

private:
	std::string GetFileName(bool bSave);
};
