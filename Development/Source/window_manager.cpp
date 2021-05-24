#include "window_manager.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <SDL\\SDL_syswm.h>

WindowManager::WindowManager(LibraryLoader& libraryLoader) :
	_window(libraryLoader.getWindowPointer())
{
	hideBorder();
	disableVsync();	
}

WindowManager::~WindowManager()
{
	SDL_DestroyWindow(_window);
}

void WindowManager::setTitle(const string& title)
{
	SDL_SetWindowTitle(_window, title.c_str());
}

void WindowManager::setSize(Ivec2 size)
{
	SDL_SetWindowSize(_window, size.x, size.y);
	center();
}

void WindowManager::center()
{
	SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void WindowManager::setOpacity(float value)
{
	SDL_SetWindowOpacity(_window, value);
}

void WindowManager::enableColorKeying(Vec3 color)
{
	// Get window handle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_window, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

	// Set transparency color
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(static_cast<int>(color.r * 255.0f), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255)), 0, LWA_COLORKEY);
}

void WindowManager::disableColorKeying(Vec3 color)
{
	// Get window handle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_window, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;
	
	// Remove opaqueness property
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, RGB(static_cast<int>(color.r * 255.0f), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255)), 0, LWA_ALPHA);
}

void WindowManager::showBorder()
{
	SDL_SetWindowBordered(_window, SDL_TRUE);
}

void WindowManager::hideBorder()
{
	SDL_SetWindowBordered(_window, SDL_FALSE);
}

void WindowManager::enableFullscreen()
{
	SDL_SetWindowFullscreen(_window, SDL_TRUE);
}

void WindowManager::disableFullscreen()
{
	SDL_SetWindowFullscreen(_window, SDL_FALSE);
}

void WindowManager::enableVsync()
{
	SDL_GL_SetSwapInterval(1);
}

void WindowManager::disableVsync()
{
	SDL_GL_SetSwapInterval(0);
}

void WindowManager::swapBackBuffer()
{
	SDL_GL_SwapWindow(_window);
}

void WindowManager::showWindow()
{
	SDL_ShowWindow(_window);
}

void WindowManager::hideWindow()
{
	SDL_HideWindow(_window);
}

void WindowManager::showCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}

void WindowManager::hideCursor()
{
	SDL_ShowCursor(SDL_DISABLE);
}

void WindowManager::setCursorPos(Ivec2 pos)
{
	SDL_WarpMouseInWindow(_window, pos.x, pos.y);
}

const Ivec2 WindowManager::getCursorPos() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return Ivec2(x, y);
}

bool WindowManager::isCursorVisible() const
{
	return static_cast<bool>(SDL_ShowCursor(SDL_QUERY));
}