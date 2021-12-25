#pragma once

#include <SDL\\SDL.h>
#include <string>

using std::string;

class LibraryLoader final
{
public:
	LibraryLoader();
	~LibraryLoader();

	const string getCpuModel() const;
	const string getGpuModel() const;
	const string getOpenglVersion() const;

	SDL_Window* getWindowPointer();

private:
	SDL_Window* _windowPointer = nullptr;
};