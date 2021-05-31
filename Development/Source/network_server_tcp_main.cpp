#define WIN32_LEAN_AND_MEAN

#include "network_server_tcp.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkServerTCP::NetworkServerTCP() :
	_connectionSocketID(INVALID_SOCKET)
{

}

NetworkServerTCP::~NetworkServerTCP()
{
	if (_isRunning)
	{
		stop();
	}
}

void NetworkServerTCP::start(unsigned int customMaxClientCount)
{
	// Must not be running
	if (_isRunning)
	{
		Logger::throwWarning("Trying to start networking server: already running!");
		return;
	}

	// Check if custom client count is not too high
	if ((customMaxClientCount > NetworkUtils::MAX_CLIENT_COUNT) || (customMaxClientCount <= 0))
	{
		Logger::throwWarning("Trying to start networking server: invalid maximum client count!");
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
	auto infoStatusCode = getaddrinfo(nullptr, NetworkUtils::SERVER_PORT.c_str(), &hints, &addressInfo);
	if (infoStatusCode != 0)
	{
		Logger::throwError("Network server startup (address info) failed with error code: ", infoStatusCode);
		return;
	}

	// Create socket for listening to client connection requests
	_connectionSocketID = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (_connectionSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking server startup (socket create) failed with error code: ", WSAGetLastError());
	}

	// Add options to the connection socket
	DWORD optionValue = 1;
	setsockopt(_connectionSocketID, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&optionValue), sizeof(optionValue));

	// Bind the listening socket
	auto bindStatusCode = bind(_connectionSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if (bindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking server startup (socket bind) failed with error code: ", WSAGetLastError());
	}

	// Address info not needed anymore
	freeaddrinfo(addressInfo);

	// Enable listening for any incoming client connection request
	auto listenStatusCode = listen(_connectionSocketID, SOMAXCONN);
	if (listenStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking server startup (socket listen) failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for accepting incoming connection requests
	_connectionThread = std::async(std::launch::async, &NetworkServerTCP::_waitForClientConnection, this, _connectionSocketID);

	// Server is now operable
	_customMaxClientCount = customMaxClientCount;
	_isRunning = true;

	// Logging
	Logger::throwInfo("Started network server!");
}

void NetworkServerTCP::stop()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Trying to stop networking server: not running!");
		return;
	}

	// Close listening socket
	closesocket(_connectionSocketID);

	// Delete all connected clients
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		_disconnectClient(_clientSocketIDs[i]);
	}

	// Miscellaneous
	_pendingMessages.clear();
	_currentMessageBuild = "";
	_connectionSocketID = INVALID_SOCKET;
	_customMaxClientCount = NetworkUtils::MAX_CLIENT_COUNT;
	_isRunning = false;

	// Logging
	Logger::throwInfo("Stopped network server!");
}