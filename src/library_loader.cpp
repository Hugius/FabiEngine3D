#define WIN32_LEAN_AND_MEAN

#include "library_loader.hpp"
#include "logger.hpp"

#include <winsock2.h>

LibraryLoader::LibraryLoader()
{
	WSADATA winsockData;

	auto winsockStatus = WSAStartup(MAKEWORD(2, 2), &winsockData);

	if(winsockStatus == 0)
	{
		Logger::throwInfo("Initialized WinSock");
	}
	else
	{
		Logger::throwError("WinSock could not be initialized: ", winsockStatus);
	}
}

LibraryLoader::~LibraryLoader()
{
	WSACleanup();
}

HWND LibraryLoader::getWindowHandle()
{
	return _windowHandle;
}