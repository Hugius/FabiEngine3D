#pragma once

#include "mathematics.hpp"
#include "library_loader.hpp"

#include <SDL\\SDL.h>
#include <string>

using std::string;

class WindowManager final
{
public:
	WindowManager(LibraryLoader& libraryLoader);
	~WindowManager();
	
	void setTitle(const string & title);
	void setSize(Ivec2 size);
	void center();
	void setOpacity(float value);
	void enableColorKeying(Vec3 color);
	void disableColorKeying(Vec3 color);
	void showBorder();
	void hideBorder();
	void enableFullscreen();
	void disableFullscreen();
	void enableVsync();
	void disableVsync();
	void swapBackBuffer();
	void showWindow();
	void hideWindow();
	void showCursor();
	void hideCursor();
	void setCursorPos(Ivec2 pos);

	const Ivec2 getCursorPos() const;
	bool isCursorVisible() const;

private:
	SDL_Window * _window = nullptr;
};