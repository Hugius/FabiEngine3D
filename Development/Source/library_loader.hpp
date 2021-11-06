#pragma once

#include <SDL\\SDL.h>
#include <string>

using std::string;

class LibraryLoader final
{
public:
	LibraryLoader();
	~LibraryLoader();

	// Strings
	const string getCpuModel() const;
	const string getGpuModel() const;
	const string getOpenglVersion() const;

	// Miscellaneous
	SDL_Window* getWindowPointer();

private:
	// Miscellaneous
	SDL_Window* _windowPointer = nullptr;
};