#pragma once

#include <SDL\\SDL.h>
#include <string>

using std::string;

class LibraryLoader final
{
public:
	LibraryLoader();
	~LibraryLoader();

	// STRING
	const string getCpuModel() const;
	const string getGpuModel() const;
	const string getOpenglVersion() const;

	// MISCELLANEOUS
	SDL_Window* getWindowPointer();

private:
	// MISCELLANEOUS
	SDL_Window* _windowPointer = nullptr;
};