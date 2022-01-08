#define WIN32_LEAN_AND_MEAN

#include "library_loader.hpp"
#include "logger.hpp"

#include <SDL_mixer.h>
#include <glew.h>
#include <winsock2.h>
#include <ShellScalingAPI.h>

LibraryLoader::LibraryLoader()
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);

	Logger::throwInfo("Initializing SDL...");
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::throwFatalWarning("SDL could not be initialized: ", SDL_GetError());
	}

	Logger::throwInfo("Initializing window...");
	_windowPointer = SDL_CreateWindow("FabiEngine3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
									  SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(_windowPointer);

	Logger::throwInfo("Initializing OpenGL...");
	auto initGlew = glewInit();
	if(initGlew != GLEW_OK)
	{
		Logger::throwFatalWarning("GLEW could not be initialized: ", reinterpret_cast<char const*>(glewGetErrorString(initGlew)));
	}

	Logger::throwInfo("Initializing SDL_Mixer...");
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		Logger::throwFatalWarning("SDL_MIX could not be initialized: ", Mix_GetError());
	}

	Logger::throwInfo("Initializing Sockets API...");
	WSADATA wsaData;
	auto winsockResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(winsockResult != 0)
	{
		Logger::throwFatalWarning("Windows Sockets API could not be initialized: ", winsockResult);
	}
}

LibraryLoader::~LibraryLoader()
{
	WSACleanup();
	Mix_Quit();
	SDL_Quit();
}

SDL_Window* LibraryLoader::getWindowPointer()
{
	auto temp = _windowPointer;
	_windowPointer = nullptr;
	return temp;
}