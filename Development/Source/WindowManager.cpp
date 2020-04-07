#include <GLEW/glew.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include <WE3D/WindowManager.hpp>
#include <WE3D/Logger.hpp>
#include <WE3D/Configuration.hpp>

WindowManager::WindowManager()
{
	// SDL stuff
	Logger::getInst().throwInfo("Initializing SDL 2...");
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		string error = "SDL could not be initialized: " + string(SDL_GetError());
		Logger::getInst().throwError(error.c_str());
	}

	// Window stuff
	Logger::getInst().throwInfo("Initializing window...");
	p_window = SDL_CreateWindow(
		"WoodEngine3D Application(32 bit)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
		SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
	p_context = SDL_GL_CreateContext(p_window);
	hideBorder();

	// Glew
	Logger::getInst().throwInfo("Initializing glew...");
	glewExperimental = GL_TRUE;
	GLenum initGlew = glewInit();
	if (initGlew != GLEW_OK)
	{
		Logger::getInst().throwError(reinterpret_cast<char const *>(glewGetErrorString(initGlew)));
	}
	Logger::getInst().throwInfo("Using GLEW version " + string(reinterpret_cast<char const *>(glewGetString(GLEW_VERSION))));

	// Image stuff
	Logger::getInst().throwInfo("Initializing SDL_Image...");
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		string error = "SDL_IMG could not be initialized:: " + string(IMG_GetError());
		Logger::getInst().throwError(error.c_str());
	}

	// Text stuff
	Logger::getInst().throwInfo("Initializing SDL_TTF...");
	TTF_Init();
	if (TTF_Init() == -1)
	{
		string error = "SDL_TTF could not be initialized: " + string(TTF_GetError());
		Logger::getInst().throwError(error.c_str());
	}

	// Audio stuff
	Logger::getInst().throwInfo("Initializing SDL_Mixer...");
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		string error = "SDL_Mixer could not be initialized: " + string(Mix_GetError());
		Logger::getInst().throwError(error.c_str());
	}

	// SDL stuff
	Logger::getInst().throwInfo("Initializing SDL settings...");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetSwapInterval(Config::getInst().isWindowVsynced());
}

WindowManager::~WindowManager()
{
	SDL_DestroyWindow(p_window);
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void WindowManager::setTitle(const string & title)
{
	SDL_SetWindowTitle(p_window, title.c_str());
}

void WindowManager::setSize(ivec2 size)
{
	SDL_SetWindowSize(p_window, size.x, size.y);
	SDL_SetWindowPosition(p_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void WindowManager::showBorder()
{
	SDL_SetWindowBordered(p_window, SDL_TRUE);
}

void WindowManager::hideBorder()
{
	SDL_SetWindowBordered(p_window, SDL_FALSE);
}

void WindowManager::enableFullscreen()
{
	SDL_SetWindowFullscreen(p_window, SDL_TRUE);
}

void WindowManager::disableFullscreen()
{
	SDL_SetWindowFullscreen(p_window, SDL_FALSE);
}

void WindowManager::swapBackBuffer()
{
	SDL_GL_SwapWindow(p_window);
}

void WindowManager::showWindow()
{
	SDL_ShowWindow(p_window);
}

void WindowManager::hideWindow()
{
	SDL_HideWindow(p_window);
}

void WindowManager::showMouseCursor()
{
	SDL_ShowCursor(true);
}

void WindowManager::hideMouseCursor()
{
	SDL_ShowCursor(false);
}

void WindowManager::setMousePos(ivec2 pos)
{
	SDL_WarpMouseInWindow(p_window, pos.x, pos.y);
}

const ivec2 WindowManager::getMousePos() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return ivec2(x, y);
}