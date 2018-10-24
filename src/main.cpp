#include "main.h"
#include <iostream>

Life::Life()
	: m_pWnd{nullptr}
	, m_pGame{nullptr}
	, m_pMenu{nullptr}
	, m_bRun{false}
	, m_frameTime{std::chrono::nanoseconds(0)}
	, m_iDelay{33333333}
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		throw "SDL_INIT";
	if (!(m_pWnd = CreateWindow()))
		throw "CreateWindow";
	if (!(m_pMenu = new Menu(m_pWnd)))
		throw "SDL_GL_CreateContext";
	if (!(m_pGame = new Game(m_pWnd)))
		throw "SDL_GL_CreateContext";
	OnResize();
}

SDL_Window* Life::CreateWindow()
{
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
		return nullptr;
	return SDL_CreateWindow("Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1024, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}


Life::~Life()
{
	delete m_pGame;
	delete m_pMenu;
	SDL_DestroyWindow(m_pWnd);
	SDL_Quit();
}

int Life::Run(int argc, char* argv[])
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
				m_frameTime += std::chrono::nanoseconds(std::max(m_iDelay, -wait.count()));
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
	return 0;
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
		}
		break;
	case SDL_KEYDOWN:
		switch(pEvent->key.keysym.scancode)
		{
		case SDL_SCANCODE_RETURN:
			if (pEvent->key.repeat == 0 && !m_bRun)
			{
				m_frameTime = std::chrono::steady_clock::now();
				m_bRun = true;
				Tick();
				m_bRun = false;
				Tick();
			}
			break;
		case SDL_SCANCODE_SPACE:
			if (pEvent->key.repeat == 0)
			{
				m_bRun = !m_bRun;
				if (m_bRun)
					m_frameTime = std::chrono::steady_clock::now();
			}
			break;
		case SDL_SCANCODE_ESCAPE:
			if (pEvent->key.repeat == 0)
				m_bRun = false;
			break;
		case SDL_SCANCODE_L:
			if (pEvent->key.repeat == 0 && !m_bRun)
			{
				m_pGame->Load();
				Tick();
			}
			break;
		case SDL_SCANCODE_S:
			if (pEvent->key.repeat == 0 && !m_bRun)
			{
				m_pGame->Save();
				Tick();
			}
			break;
		case SDL_SCANCODE_UP:
			if (m_iDelay > 0ll)
			{
				m_frameTime -= std::chrono::nanoseconds(m_iDelay);
				m_iDelay = m_iDelay * 8 / 10;
				m_frameTime += std::chrono::nanoseconds(m_iDelay);
				if (!m_bRun)
					Tick();
			}
			break;
		case SDL_SCANCODE_DOWN:
			if (m_iDelay < (100ll * 1000ll * 1000ll * 1000ll))
			{
				m_frameTime -= std::chrono::nanoseconds(m_iDelay);
				m_iDelay = (m_iDelay + 1) * 10 / 8;
				m_frameTime += std::chrono::nanoseconds(m_iDelay);
				if (!m_bRun)
					Tick();
			}
			break;
		}
		break;
	}
	return 0;
}

void Life::OnResize()
{
	m_pMenu->SetWindowSize();
	m_pGame->SetWindowSize();
	m_pGame->SetPointSize();
	bool bRun = m_bRun;
	m_bRun = false;
	Tick();
	m_bRun = bRun;
	if (!m_bRun)
		Tick();
}

void Life::Tick()
{
	static std::chrono::steady_clock::time_point GameUpdate(std::chrono::nanoseconds(0));
	static std::chrono::steady_clock::time_point MenuUpdate(std::chrono::nanoseconds(0));
	static int64_t FrameCount = 0;
	FrameCount += m_bRun;
	int64_t duration = (m_frameTime - GameUpdate).count();
	bool bUpdateGame = !m_bRun || duration > (50ll * 1000ll * 1000ll);
	m_pGame->Tick(bUpdateGame, m_bRun);
	if (bUpdateGame)
	{
		static int64_t iSpeed = 0;
		int64_t duration = (m_frameTime - MenuUpdate).count();
		bool bUpdateMenu = !m_bRun || duration > (500ll * 1000ll * 1000ll);
		if (bUpdateMenu)
		{
			iSpeed = FrameCount == 0 ? 0 : FrameCount * (1000ll * 1000ll * 1000ll) / duration;
			FrameCount = 0;
			MenuUpdate = m_frameTime;
		}
		m_pMenu->Tick(bUpdateMenu, iSpeed , m_iDelay > 0 ? (1000ll * 1000ll * 1000ll) / m_iDelay : 0ll);
		SDL_GL_SwapWindow(m_pWnd);
		GameUpdate = m_frameTime;
	}
}

int main(int argc, char* argv[])
{
	try
	{
		Life life;
		life.Run(argc, argv);
	}
	catch(const char* szE)
	{
		std::cout << "Exception: " << szE << std::endl;
		return -1;
	}
	return 0;
}
