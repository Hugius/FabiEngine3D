#pragma once

#include <windows.h>

class LibraryLoader final
{
public:
	LibraryLoader();
	~LibraryLoader();

	HWND getWindowHandle();

private:
	HWND _windowHandle = nullptr;
};