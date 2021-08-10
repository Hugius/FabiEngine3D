#pragma once

#include <SDL\\SDL.h>
#include <string>

using std::string;

class LibraryLoader final
{
public:
	LibraryLoader();
	~LibraryLoader();

	SDL_Window* getWindowPointer();

	const string getGpuModel();
	const string getOpenglVersion();

private:
	SDL_Window* _windowPointer = nullptr;
};