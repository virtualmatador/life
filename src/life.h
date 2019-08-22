#pragma once

#include "menu.h"
#include "game.h"

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>

#include <chrono>
#include <string>

class Life
{
private:
	Menu* m_pMenu;
	Game* m_pGame;
	SDL_Cursor* m_pNormal;
	SDL_Cursor* m_pEdit;

public:
	SDL_Window* m_pWnd;
	SDL_Point m_ptClient;
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
	void Run();

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
	void CreateWnd();
	int HandleEvent(SDL_Event* pEvent);
	void OnResize();
	void OnMove();
	void Refresh();
	void Tick();
	void Click(int iX, int iY);
};
