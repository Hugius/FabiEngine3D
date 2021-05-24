#pragma once

#include <SDL\\SDL.h>

class LibraryLoader final
{
public:
	LibraryLoader();
	~LibraryLoader();

	SDL_Window* getWindowPointer();

private:
	SDL_Window* _window = nullptr;
};