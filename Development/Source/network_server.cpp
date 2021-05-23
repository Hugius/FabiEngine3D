#include "network_server.hpp"
#include "logger.hpp"

NetworkServer::NetworkServer()
{
	// Data structure to hold implementation info
	WSADATA wsaData;

	// Initialize WinSock at max version 2.2
	auto startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (startupResult != 0)
	{
		Logger::throwError("Networking startup failed with error code: ", startupResult);
	}
}