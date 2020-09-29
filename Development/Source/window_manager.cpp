#include "window_manager.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <GLEW\\glew.h>
#include <SDL\\SDL_image.h>
#include <SDL\\SDL_mixer.h>
#include <SDL\\SDL_ttf.h>
#include <SDL\\SDL_syswm.h>
#include <Windows.h>
#include <ShellScalingAPI.h>

WindowManager::WindowManager()
{
	// Make sure scaled monitors still show the correct resolution
	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);

	// SDL stuff
	Logger::throwInfo("Initializing SDL 2...");
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		string error = "SDL could not be initialized: " + string(SDL_GetError());
		Logger::throwError(error.c_str());
	}
	
	// Window stuff
	Logger::throwInfo("Initializing window...");
	_window = SDL_CreateWindow(
		"FabiEngine3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
		SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
	_context = SDL_GL_CreateContext(_window);
	hideBorder();

	// GLEW (GL Extension Wrangler)
	Logger::throwInfo("Initializing glew...");
	glewExperimental = GL_TRUE;
	GLenum initGlew = glewInit();
	if (initGlew != GLEW_OK) // Error
	{
		Logger::throwError(reinterpret_cast<char const *>(glewGetErrorString(initGlew)));
	}
	//Logger::throwInfo("Using GLEW version " + string(reinterpret_cast<char const *>(glewGetString(GLEW_VERSION))));

	// Image stuff
	Logger::throwInfo("Initializing SDL_Image...");
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		string error = "SDL_IMG could not be initialized:: " + string(IMG_GetError());
		Logger::throwError(error.c_str());
	}

	// Text stuff
	Logger::throwInfo("Initializing SDL_TTF...");
	TTF_Init();
	if (TTF_Init() == -1)
	{
		string error = "SDL_TTF could not be initialized: " + string(TTF_GetError());
		Logger::throwError(error.c_str());
	}

	// Audio stuff
	Logger::throwInfo("Initializing SDL_Mixer...");
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		string error = "SDL_Mixer could not be initialized: " + string(Mix_GetError());
		Logger::throwError(error.c_str());
	}

	// SDL stuff
	Logger::throwInfo("Initializing SDL settings...");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetSwapInterval(0);
}

WindowManager::~WindowManager()
{
	SDL_DestroyWindow(_window);
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void WindowManager::setTitle(const string& title)
{
	SDL_SetWindowTitle(_window, title.c_str());
}

void WindowManager::setSize(ivec2 size)
{
	SDL_SetWindowSize(_window, size.x, size.y);
	SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void WindowManager::setOpacity(float value)
{
	SDL_SetWindowOpacity(_window, value);
}

void WindowManager::makeColorOpaque(vec3 color)
{
	// Get window handle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_window, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

	// Set transparency color
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(static_cast<int>(color.r * 255.0f), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255)), 0, LWA_COLORKEY);
}

void WindowManager::showBorder()
{
	SDL_SetWindowBordered(_window, SDL_TRUE);
}

void WindowManager::hideBorder()
{
	SDL_SetWindowBordered(_window, SDL_FALSE);
}

void WindowManager::enableFullscreen()
{
	SDL_SetWindowFullscreen(_window, SDL_TRUE);
}

void WindowManager::disableFullscreen()
{
	SDL_SetWindowFullscreen(_window, SDL_FALSE);
}

void WindowManager::swapBackBuffer()
{
	SDL_GL_SwapWindow(_window);
}

void WindowManager::showWindow()
{
	SDL_ShowWindow(_window);
}

void WindowManager::hideWindow()
{
	SDL_HideWindow(_window);
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
	SDL_WarpMouseInWindow(_window, pos.x, pos.y);
}

const ivec2 WindowManager::getMousePos() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return ivec2(x, y);
}