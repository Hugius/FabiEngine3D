#define WIN32_LEAN_AND_MEAN

#include "network_client.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkClient::NetworkClient() :
	_serverSocketID(INVALID_SOCKET)
{

}

NetworkClient::~NetworkClient()
{
	if (_isRunning)
	{
		stop();
	}
}

void NetworkClient::start(const string& serverIP, const string& serverPort)
{
	// Validate runtime status
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

void NetworkClient::stop()
{
	// Validate runtime status
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
	_serverSocketID = INVALID_SOCKET;
	_addressInfo = nullptr;
	_receivedMessage = nullptr;
	_isRunning = false;
	_isConnectedToServer = false;
}