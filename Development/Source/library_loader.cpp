#define WIN32_LEAN_AND_MEAN

#include "library_loader.hpp"
#include "logger.hpp"

#include <GLEW\\glew.h>
#include <SDL\\SDL_image.h>
#include <SDL\\SDL_mixer.h>
#include <SDL\\SDL_ttf.h>
#include <SDL\\SDL_syswm.h>

#include <winsock2.h>
#include <ShellScalingAPI.h>

LibraryLoader::LibraryLoader()
{
	// Make sure scaled monitors still show the correct resolution
	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);

	// SDL2
	Logger::throwInfo("Initializing SDL...");
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::throwError("SDL could not be initialized: ", SDL_GetError());
	}

	// SDL_Window
	Logger::throwInfo("Initializing window...");
	_windowPointer = SDL_CreateWindow("FabiEngine3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
		SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(_windowPointer);

	// GLEW (OpenGL Extension Wrangler)
	Logger::throwInfo("Initializing OpenGL...");
	glewExperimental = GL_TRUE;
	GLenum initGlew = glewInit();
	if (initGlew != GLEW_OK)
	{
		Logger::throwError("GLEW could not be initialized: ", reinterpret_cast<char const*>(glewGetErrorString(initGlew)));
	}

	// SDL_image
	Logger::throwInfo("Initializing SDL_Image...");
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		Logger::throwError("SDL_IMG could not be initialized: ", IMG_GetError());
	}

	// SDL_ttf
	Logger::throwInfo("Initializing SDL_TTF...");
	if (TTF_Init() == -1)
	{
		Logger::throwError("SDL_TTF could not be initialized: ", TTF_GetError());
	}

	// SDL_mixer
	Logger::throwInfo("Initializing SDL_Mixer...");
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		Logger::throwError("SDL_Mixer could not be initialized: ", Mix_GetError());
	}

	// Winsock2
	WSADATA wsaData;
	auto winsockResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (winsockResult != 0)
	{
		Logger::throwError("Windows Sockets API could not be initialized: ", winsockResult);
	}

	// Miscellaneous stuff
	Logger::throwInfo("Initializing SDL settings...");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}

LibraryLoader::~LibraryLoader()
{
	WSACleanup();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

SDL_Window* LibraryLoader::getWindowPointer()
{
	// Can be retrieved only once
	auto temp = _windowPointer;
	_windowPointer = nullptr;
	return temp;
}