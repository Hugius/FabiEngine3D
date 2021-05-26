#define WIN32_LEAN_AND_MEAN

#include "network_server.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkServer::NetworkServer() :
	_listeningSocketID(INVALID_SOCKET)
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
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // Ipv4 address
	hints.ai_socktype = SOCK_STREAM; // Streaming socket
	hints.ai_protocol = IPPROTO_TCP; // TCP protocol
	hints.ai_flags = AI_PASSIVE; // Flag to indicate passive server socket instead of connecting client socket

	// Create address info
	struct addrinfo* addressInfo = nullptr;
	auto infoStatusCode = getaddrinfo(nullptr, networkServer_PORT.c_str(), &hints, &addressInfo);
	if (infoStatusCode != 0)
	{
		Logger::throwError("Network server startup (address info) failed with error code: ", infoStatusCode);
		return;
	}

	// Create socket for listening
	_listeningSocketID = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (_listeningSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Network server startup (listening socket create) failed with error code: ", WSAGetLastError());
	}

	// Bind the listening socket
	auto bindStatusCode = bind(_listeningSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if (bindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Network server startup (listening socket bind) failed with error code: ", WSAGetLastError());
	}

	// Address info not needed anymore
	freeaddrinfo(addressInfo);

	// Enable listening for any incoming client connection message
	auto listenStatusCode = listen(_listeningSocketID, SOMAXCONN);
	if (listenStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Network server startup (socket listen) failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for accepting incoming connection requests
	_connectionThread = std::async(std::launch::async, &NetworkServer::_waitForClientConnection, this, _listeningSocketID);

	// Server is now operable
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

	// Close listening socket
	closesocket(_listeningSocketID);

	// Delete all connected clients
	for (auto& ip : _clientIPs)
	{
		_disconnectClient(ip);
	}

	// Miscellaneous
	_listeningSocketID = INVALID_SOCKET;
	_isRunning = false;
}