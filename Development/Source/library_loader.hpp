#pragma once

#include <SDL\\SDL.h>

class LibraryLoader final
{
public:
	LibraryLoader();
	~LibraryLoader();

	SDL_Window* getWindowPointer() const;

private:
	SDL_Window* _windowPointer = nullptr;
};