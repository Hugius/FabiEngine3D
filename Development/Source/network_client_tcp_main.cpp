#define WIN32_LEAN_AND_MEAN

#include "network_client_tcp.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkClientTCP::NetworkClientTCP() :
	_serverSocketID(INVALID_SOCKET)
{

}

NetworkClientTCP::~NetworkClientTCP()
{
	if (_isRunning)
	{
		stop();
	}
}

void NetworkClientTCP::start(const string& serverIP, const string& serverPort)
{
	// Must not be running
	if (_isRunning)
	{
		Logger::throwWarning("Trying to start networking client: already running!");
		return;
	}

	// Compose address info hints
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // Ipv4 address
	hints.ai_socktype = SOCK_STREAM; // Streaming socket
	hints.ai_protocol = IPPROTO_TCP; // TCP protocol

	// Create address info
	auto infoStatusCode = getaddrinfo(serverIP.c_str(), serverPort.c_str(), &hints, &_addressInfo);
	if (infoStatusCode != 0)
	{
		Logger::throwError("Networking client startup (address info) failed with error code: ", infoStatusCode);
		return;
	}

	// Start attempting to connect
	_initiateConnection();

	// Client is now operable
	_isRunning = true;
}

void NetworkClientTCP::stop()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Trying to stop networking client: not running!");
		return;
	}

	// Close connection socket
	closesocket(_serverSocketID);

	// Delete address info
	if (_addressInfo != nullptr)
	{
		freeaddrinfo(_addressInfo);
	}

	// Miscellaneous
	_pendingMessages.clear();
	_currentMessageBuild = "";
	_serverSocketID = INVALID_SOCKET;
	_addressInfo = nullptr;
	_isRunning = false;
	_isConnectedToServer = false;
}