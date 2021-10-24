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

	const string getCpuModel() const;
	const string getGpuModel() const;
	const string getOpenglVersion() const;

private:
	SDL_Window* _windowPointer = nullptr;
};