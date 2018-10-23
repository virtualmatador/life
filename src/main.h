#pragma once

#include "menu.h"
#include "game.h"

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#include <chrono>
#include <string>

class Life
{
private:
	SDL_Window* m_pWnd;
	Menu* m_pMenu;
	Game* m_pGame;

	bool m_bRun;
	std::chrono::steady_clock::time_point m_frameTime;
	int64_t m_iDelay;

public:
	Life();
	~Life();
	int Run(int argc, char* argv[]);

private:
	SDL_Window* CreateWindow();
	int HandleEvent(SDL_Event* pEvent);
	void OnResize();
	void Tick();
};
