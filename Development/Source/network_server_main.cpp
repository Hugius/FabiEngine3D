#define WIN32_LEAN_AND_MEAN

#include "network_server.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkServer::NetworkServer() :
	_listenSocketID(INVALID_SOCKET)
{

}

NetworkServer::~NetworkServer()
{
	if (_isRunning)
	{
		stop();
	}
}

void NetworkServer::start()
{
	// Validate runtime status
	if (_isRunning)
	{
		Logger::throwWarning("Trying to start networking server: already running!");
		return;
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
	auto infoStatusCode = getaddrinfo(NULL, SERVER_PORT.c_str(), &hints, &addressInfo);
	if (infoStatusCode != 0)
	{
		Logger::throwError("Network server startup (address info) failed with error code: ", infoStatusCode);
		return;
	}

	// Create socket for listening
	_listenSocketID = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (_listenSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Network server startup (socket create) failed with error code: ", WSAGetLastError());
	}

	// Bind the listening socket
	auto bindStatusCode = bind(_listenSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if (bindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Network server startup (socket bind) failed with error code: ", WSAGetLastError());
	}

	// Address info not needed anymore
	freeaddrinfo(addressInfo);

	// Enable listening for any client connection requests
	auto listenStatusCode = listen(_listenSocketID, SOMAXCONN);
	if (listenStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Network server startup (socket listen) failed with error code: ", WSAGetLastError());
	}

	// Spawn an initial thread for accepting incoming connection requests
	_connectionThread = std::async(std::launch::async, &NetworkServer::_waitForClientConnection, this, _listenSocketID);

	_isRunning = true;
}

void NetworkServer::stop()
{
	// Validate runtime status
	if (!_isRunning)
	{
		Logger::throwWarning("Trying to stop networking server: not running!");
		return;
	}

	// Close all network sockets
	closesocket(_listenSocketID);
	for (auto& socketID : _clientSocketIDs)
	{
		closesocket(socketID);
	}

	// Miscellaneous
	_clientSocketIDs.clear();
	_clientIPs.clear();
	_clientMessageThreads.clear();
	_listenSocketID = INVALID_SOCKET;
	_isRunning = false;
}