#define WIN32_LEAN_AND_MEAN

#include "library_loader.hpp"
#include "logger.hpp"

#include <glew.h>
#include <winsock2.h>
#include <ShellScalingAPI.h>

LibraryLoader::LibraryLoader()
{
	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::throwError("SDL could not be initialized: ", SDL_GetError());
	}
	Logger::throwInfo("Initialized SDL");

	_windowPointer = SDL_CreateWindow("FabiEngine3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
									  SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(_windowPointer);
	Logger::throwInfo("Initialized window");

	auto initGlew = glewInit();
	if(initGlew != GLEW_OK)
	{
		Logger::throwError("GLEW could not be initialized: ", reinterpret_cast<char const *>(glewGetErrorString(initGlew)));
	}
	Logger::throwInfo("Initialized OpenGL");

	WSADATA wsaData;
	auto winsockResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(winsockResult != 0)
	{
		Logger::throwError("WinSock could not be initialized: ", winsockResult);
	}
	Logger::throwInfo("Initialized WinSock");
}

LibraryLoader::~LibraryLoader()
{
	WSACleanup();
	SDL_Quit();
}

SDL_Window * LibraryLoader::getWindowPointer()
{
	auto temp = _windowPointer;
	_windowPointer = nullptr;
	return temp;
}