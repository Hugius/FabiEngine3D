#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkClientAPI::NetworkClientAPI() :
	_serverSocketID(INVALID_SOCKET)
{

}

NetworkClientAPI::~NetworkClientAPI()
{
	if (_isRunning)
	{
		stop();
	}
}

void NetworkClientAPI::start(const string& username)
{
	// Must not be running
	if (_isRunning)
	{
		Logger::throwWarning("Networking client tried to start: already running!");
		return;
	}

	// Validate username
	if (username.empty())
	{
		Logger::throwWarning("Networking client tried to start: empty username!");
		return;
	}
	else if (NetworkUtils::isMessageReserved(username))
	{
		Logger::throwWarning("Networking client tried to start: username is reserved!");
		return;
	}
	else
	{
		_username = username;
	}

	// Client is now operable
	_isRunning = true;
}

void NetworkClientAPI::connectToServer(const string& serverIP, const string& serverPort)
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to connect: not running!");
		return;
	}

	// Must not already be connected
	if (_isConnectedToServer)
	{
		Logger::throwWarning("Networking client tried to connect: already connected!");
		return;
	}

	// Must not already be connecting
	if (_isConnectingToServer)
	{
		Logger::throwWarning("Networking client tried to connect: already connecting!");
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
		Logger::throwError("Networking client address info failed with error code: ", infoStatusCode);
		return;
	}

	// Create socket for connecting to the server
	_serverSocketID = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);
	if (_serverSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking client startup (socket create) failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for connecting to the server
	_connectionThread = std::async(std::launch::async, &NetworkClientAPI::_waitForServerConnection, this, _serverSocketID, _addressInfo);

	// Client is now connecting
	_isConnectingToServer = true;
}

void NetworkClientAPI::disconnectFromServer()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to disconnect: not running!");
		return;
	}

	// Must be connected first
	if (!_isConnectedToServer)
	{
		Logger::throwWarning("Networking client tried to disconnect: not connected!");
		return;
	}

	// Close server connection
	closesocket(_serverSocketID);

	// Delete address info
	if (_addressInfo != nullptr)
	{
		freeaddrinfo(_addressInfo);
	}

	// Reset variables
	_serverSocketID = INVALID_SOCKET;
	_addressInfo = nullptr;
	_pendingMessages.clear();
	_serverPings.clear();
	_lastMilliseconds = 0;
	_currentMessageBuild = "";
	_isConnectedToServer = false;
	_isAcceptedByServer = false;
	_isWaitingForPing = false;
}

void NetworkClientAPI::stop()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Trying to stop networking client: not running!");
		return;
	}

	// Disconnect if connected
	if (_isConnectedToServer)
	{
		disconnectFromServer();
	}

	// Reset variables
	_username = "";
	_isRunning = false;
}