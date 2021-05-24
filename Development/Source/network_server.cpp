#define WIN32_LEAN_AND_MEAN

#include "network_server.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

void NetworkServer::start()
{
	// Error checking
	if (_isRunning)
	{
		Logger::throwError("Trying to start network server: already running!");
	}

	// Compose address info hints
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // Ipv4 address
	hints.ai_socktype = SOCK_STREAM; // Streaming socket
	hints.ai_protocol = IPPROTO_TCP; // TCP protocol
	hints.ai_flags = AI_PASSIVE; // Required flag

	// Create address info
	struct addrinfo* addressInfo = NULL;
	auto infoResult = getaddrinfo(NULL, SERVER_PORT.c_str(), &hints, &addressInfo);
	if (infoResult != 0)
	{
		Logger::throwError("Network server startup (address info) failed with error code: ", infoResult);
		return;
	}

	// Create socket for listening
	_listenSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (_listenSocket == INVALID_SOCKET)
	{
		Logger::throwError("Network server startup (socket create) failed with error code: ", WSAGetLastError());
	}

	// Bind the listening socket
	auto bindResult = bind(_listenSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if (bindResult == SOCKET_ERROR)
	{
		Logger::throwError("Network server startup (socket bind) failed with error code: ", WSAGetLastError());
	}

	// Address info not needed anymore
	freeaddrinfo(addressInfo);

	_isRunning = true;
}

void NetworkServer::stop()
{
	// Error checking
	if (!_isRunning)
	{
		Logger::throwError("Trying to stop network server: not running!");
	}

	closesocket(_clientSocket);
	closesocket(_listenSocket);
	WSACleanup();
	_isRunning = false;
}

void NetworkServer::update()
{
	// Error checking
	if (!_isRunning)
	{
		Logger::throwError("Trying to update network server: not running!");
	}

	auto listenResult = listen(_listenSocket, SOMAXCONN);
	if (listenResult == SOCKET_ERROR)
	{
		Logger::throwError("Network server listen failed with error code: ", WSAGetLastError());
	}

	// Accept a client socket
	_clientSocket = accept(_listenSocket, NULL, NULL);
	if (_clientSocket == INVALID_SOCKET)
	{
		Logger::throwError("Network server client accept failed with error code: ", WSAGetLastError());
	}
}