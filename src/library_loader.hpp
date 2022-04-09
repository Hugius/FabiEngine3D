#pragma once

#include <SDL.h>
#include <string>

using std::string;

class LibraryLoader final
{
public:
	LibraryLoader();
	~LibraryLoader();

	SDL_Window * getWindowPointer();

private:
	SDL_Window * _windowPointer = nullptr;
};