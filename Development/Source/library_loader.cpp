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
	// Set attributes
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// Make sure scaled monitors still show the correct resolution
	SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);

	// Initialize SDL
	Logger::throwInfo("Initializing SDL...");
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::throwFatalWarning("SDL could not be initialized: ", SDL_GetError());
	}

	// Create SDL window
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
		Logger::throwFatalWarning("GLEW could not be initialized: ", reinterpret_cast<char const*>(glewGetErrorString(initGlew)));
	}

	// Initialize SDL_image
	Logger::throwInfo("Initializing SDL_Image...");
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		Logger::throwFatalWarning("SDL_IMG could not be initialized: ", IMG_GetError());
	}

	// Initialize SDL_ttf
	Logger::throwInfo("Initializing SDL_TTF...");
	if (TTF_Init() == -1)
	{
		Logger::throwFatalWarning("SDL_TTF could not be initialized: ", TTF_GetError());
	}

	// Initialize SDL_mixer
	Logger::throwInfo("Initializing SDL_Mixer...");
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		Logger::throwFatalWarning("SDL_MIX could not be initialized: ", Mix_GetError());
	}

	// Initialize Winsock2
	WSADATA wsaData;
	auto winsockResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (winsockResult != 0)
	{
		Logger::throwFatalWarning("Windows Sockets API could not be initialized: ", winsockResult);
	}
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

// https://stackoverflow.com/questions/850774/how-to-determine-the-hardware-cpu-and-ram-on-a-machine
const string LibraryLoader::getCpuModel() const
{
	// Temporary values
	int CPUInfo[4];
	char model[48];

	// Retrieve full CPU model string
	__cpuid(CPUInfo, 0x80000002);
	memcpy(model, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000003);
	memcpy(model + 16, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000004);
	memcpy(model + 32, CPUInfo, sizeof(CPUInfo));

	// Convert to string
	string nameString;
	for (unsigned int i = 0; i < 48; i++)
	{
		nameString.push_back(model[i]);
	}

	// Remove trailing spaces
	string result;
	reverse(nameString.begin(), nameString.end());
	for (size_t i = 0; i < nameString.size(); i++)
	{
		// Check if end of whitespace found
		if (nameString[i] != 0)
		{
			result = nameString.substr(i);
			break;
		}
	}

	// Return
	reverse(result.begin(), result.end());
	return result;
}

const string LibraryLoader::getGpuModel() const
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER))));
}

const string LibraryLoader::getOpenglVersion() const
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)))).substr(0, 3);
}