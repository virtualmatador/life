#include "life.h"
#include <iostream>

Life::Life()
	: m_pGame{nullptr}
	, m_pMenu{nullptr}
	, m_pNormal{nullptr}
	, m_pEdit{nullptr}
	, m_pWnd{nullptr}
	, m_rcClient{0, 0, 0, 0}
	, m_bEdit{false}
	, m_bFrame{false}
	, m_bRun{false}
	, m_bMenu{true}
	, m_bRefresh{false}
	, m_frameTime{std::chrono::nanoseconds(0)}
	, m_FrameCount{0}
	, m_iDelay{100000}
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		throw "SDL_INIT";
	m_pNormal = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	m_pEdit = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	CreateWnd();
	if (!(m_pMenu = new Menu(this)))
		throw "SDL_GL_CreateContext";
	if (!(m_pGame = new Game(this)))
		throw "SDL_GL_CreateContext";
	OnResize();
}

Life::~Life()
{
	delete m_pGame;
	delete m_pMenu;
	SDL_DestroyWindow(m_pWnd);
	SDL_FreeCursor(m_pNormal);
	SDL_FreeCursor(m_pEdit);
	SDL_Quit();
}

void Life::CreateWnd()
{
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
		throw "SDL_GL_SetAttribute";
	float fFontX, fFontY;
	GetFontSize(&fFontX, &fFontY);
	m_pWnd = SDL_CreateWindow("Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		fFontX * 60, fFontY * 30, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!m_pWnd)
		throw "SDL_CreateWindow";
}

void Life::GetFontSize(float* pfFontX, float* pfFontY)
{
	int iDisplay  = (m_pWnd ? SDL_GetWindowDisplayIndex(m_pWnd) : 0);
	if (SDL_GetDisplayDPI(iDisplay, nullptr, pfFontX, pfFontY) < 0)
	{
		*pfFontX = 180.0f;
		*pfFontY = 180.0f;
	}
	*pfFontX /= 9.0f;
	*pfFontY /= 6.0f;
}

void Life::Run()
{
	for(;;)
	{
		SDL_Event event;
		int iEvent;
		if (m_bRun)
		{
			auto wait = m_frameTime - std::chrono::steady_clock::now();
			if (wait.count() < 0)
			{
				Tick();
				m_frameTime += std::chrono::nanoseconds(std::max(m_iDelay * 1000, -wait.count()));
				iEvent = SDL_PollEvent(&event);
			}
			else
				iEvent = SDL_WaitEventTimeout(&event, wait.count() / (1000ll * 1000ll));
		}
		else
			iEvent = SDL_WaitEvent(&event);
		if (iEvent == 1 && HandleEvent(&event) < 0)
			break;
	}
}

int Life::HandleEvent(SDL_Event* pEvent)
{
	switch (pEvent->type)
	{
	case SDL_QUIT:
		return -1;
		break;
	case SDL_WINDOWEVENT:
		switch (pEvent->window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			OnResize();
			break;
		case SDL_WINDOWEVENT_MOVED:
			OnMove();
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch(pEvent->key.keysym.scancode)
		{
		case SDL_SCANCODE_RETURN:
			if (pEvent->key.repeat == 0 && !m_bRun)
				Frame();
			break;
		case SDL_SCANCODE_SPACE:
			if (pEvent->key.repeat == 0)
				ToggleGame();
			break;
		case SDL_SCANCODE_ESCAPE:
			if (pEvent->key.repeat == 0)
				Stop();
			break;
		case SDL_SCANCODE_L:
			if (pEvent->key.repeat == 0)
				Load();
			break;
		case SDL_SCANCODE_S:
			if (pEvent->key.repeat == 0)
				Save();
			break;
		case SDL_SCANCODE_M:
			if (pEvent->key.repeat == 0)
				ToggleMenu();
			break;
		case SDL_SCANCODE_E:
			if (pEvent->key.repeat == 0)
				ToggleEdit();
			break;
		case SDL_SCANCODE_UP:
			SpeedUp();
			break;
		case SDL_SCANCODE_DOWN:
			SpeedDown();
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (pEvent->button.button)
		{
		case SDL_BUTTON_LEFT:
			Click(pEvent->button.x, pEvent->button.y);
			break;
		}
		break;
	}
	return 0;
}

void Life::UpdateClientRect()
{
	int iRight, iTop;
	SDL_GetWindowBordersSize(m_pWnd, &iTop, &m_rcClient.x, &m_rcClient.y, &iRight);
	SDL_GetWindowSize(m_pWnd, &m_rcClient.w, &m_rcClient.h);
	m_rcClient.h -= iTop + m_rcClient.y;
	m_rcClient.w -= m_rcClient.x + iRight;
}

void Life::OnResize()
{
	UpdateClientRect();
	m_pMenu->SetWindowSize();
	m_pMenu->SetFontScale();
	m_pGame->SetWindowSize();
	m_pGame->SetPointSize();
	Refresh();
	Refresh();
}

void Life::OnMove()
{
	m_pMenu->SetFontScale();
	Refresh();
}

void Life::Refresh()
{
	if (m_bEdit)
		SDL_SetCursor(m_pEdit);
	else
		SDL_SetCursor(m_pNormal);
	m_bRefresh = true;
	Tick();
	m_bRefresh = false;
}

void Life::Tick()
{
	if (m_pGame->Tick())
	{
		m_pMenu->Tick();
		SDL_GL_SwapWindow(m_pWnd);
	}
}

void Life::Click(int iX, int iY)
{
	float fX = float(iX * 2) / float(m_rcClient.w) - 1;
	float fY = float(-iY * 2) / float(m_rcClient.h) + 1;
	if (m_bEdit)
	{
		m_pGame->Edit(fX, fY);
		Refresh();
	}
	else if (m_bMenu)
		m_pMenu->HitTest(fX, fY);
}

void Life::ToggleGame()
{
	if (m_bRun)
	{
		m_bRun = false;
		Refresh();
	}
	else
	{
		if (!m_bEdit && m_pGame->HasData())
		{
			Refresh();
			m_bRun = true;
			m_frameTime = std::chrono::steady_clock::now();
		}
	}
}

void Life::ToggleMenu()
{
	m_bEdit = false;
	m_bMenu = !m_bMenu;
	Refresh();
}

void Life::ToggleEdit()
{
	if (m_bEdit)
	{
		m_bEdit = false;
		m_bRun = false;
		m_bMenu = true;
	}
	else
	{
		m_bEdit = true;
		m_bRun = false;
		m_bMenu = false;
	}
	Refresh();
}

void Life::SpeedUp()
{
	if (m_iDelay > 0ll)
	{
		m_frameTime -= std::chrono::nanoseconds(m_iDelay * 1000ll);
		m_iDelay = m_iDelay * 8 / 10;
		m_frameTime += std::chrono::nanoseconds(m_iDelay * 1000ll);
		Refresh();
	}
}

void Life::SpeedDown()
{
	if (m_iDelay < (100ll * 1000ll * 1000ll))
	{
		m_frameTime -= std::chrono::nanoseconds(m_iDelay * 1000ll);
		m_iDelay = (m_iDelay + 1) * 10 / 8;
		m_frameTime += std::chrono::nanoseconds(m_iDelay * 1000ll);
		Refresh();
	}
}

void Life::Load()
{
	m_bRun = false;
	m_pGame->Load();
	Refresh();
}

void Life::Save()
{
	m_bRun = false;
	m_pGame->Save();
	Refresh();
}

void Life::Frame()
{
	if (!m_bEdit && m_pGame->HasData())
	{
		m_frameTime = std::chrono::steady_clock::now();
		m_bRun = true;
		m_bFrame = true;
		Tick();
		m_bFrame = false;
		m_bRun = false;
		Refresh();
	}
}

void Life::Stop()
{
	m_bRun = false;
	m_bEdit = false;
	m_bMenu = true;
	Refresh();
}

int main(int argc, char* argv[])
{
	try
	{
		Life life;
		life.Run();
	}
	catch(const char* szE)
	{
		std::cout << "Exception: " << szE << std::endl;
		return -1;
	}
	return 0;
}
