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
	Menu* m_pMenu;
	Game* m_pGame;

public:
	SDL_Window* m_pWnd;
	bool m_bEdit;
	bool m_bFrame;
	bool m_bRun;
	bool m_bMenu;
	bool m_bRefresh;
	std::chrono::steady_clock::time_point m_frameTime;
	int64_t m_FrameCount;
	int64_t m_iDelay;

	
public:
	Life();
	~Life();
	void GetFontSize(float* pfFontX, float* pfFontY);
	int Run(int argc, char* argv[]);

	void ToggleGame();
	void ToggleMenu();
	void ToggleEdit();
	void SpeedUp();
	void SpeedDown();
	void Load();
	void Save();
	void Frame();
	void Stop();

private:
	void CreateWindow();
	int HandleEvent(SDL_Event* pEvent);
	void OnResize();
	void OnMove();
	void Refresh();
	void Tick();
	void Click(int iX, int iY);
};
