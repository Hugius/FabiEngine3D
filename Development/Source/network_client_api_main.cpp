#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkClientAPI::NetworkClientAPI() :
	_connectionSocketID(INVALID_SOCKET),
	_udpMessageSocketID(INVALID_SOCKET)
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
		Logger::throwWarning("Networking client tried to start: username is empty!");
		return;
	}
	else if (username.size() > NetworkUtils::MAX_USERNAME_CHARACTERS)
	{
		Logger::throwWarning("Networking client tried to start: username is too long!");
		return;
	}
	else if (NetworkUtils::isMessageReserved(username))
	{
		Logger::throwWarning("Networking client tried to start: username is reserved!");
		return;
	}
	else if (std::find(username.begin(), username.end(), ';') != username.end())
	{
		Logger::throwWarning("Networking client tried to start: username cannot contain semicolons!");
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
	// Must be running
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

	// Must be a valid IP
	if (!isValidServerIP(serverIP))
	{
		Logger::throwWarning("Networking client tried to connect: invalid server IP!");
		return;
	}

	// Save server address
	_serverIP = serverIP;
	_serverPort = serverPort;

	// Prepare for TCP connection
	_setupTCP();

	// Client is now connecting
	_isConnectingToServer = true;
}

void NetworkClientAPI::disconnectFromServer(bool mustBeAccepted)
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to disconnect: not running!");
		return;
	}

	// Must be connected & accepted
	if (!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		Logger::throwWarning("Networking client tried to disconnect: not connected!");
		return;
	}

	// Close connection socket
	if (_connectionSocketID != INVALID_SOCKET)
	{
		closesocket(_connectionSocketID);
	}

	// Close UDP message socket
	if (_udpMessageSocketID != INVALID_SOCKET)
	{
		closesocket(_udpMessageSocketID);
	}

	// Reset variables
	_connectionSocketID = INVALID_SOCKET;
	_udpMessageSocketID = INVALID_SOCKET;
	_pendingMessages.clear();
	_pingLatencies.clear();
	_lastMilliseconds = 0;
	_tcpMessageBuild = "";
	_serverIP = "";
	_serverPort = "";
	_isConnectedToServer = false;
	_isAcceptedByServer = false;
	_isWaitingForPing = false;
	_mustDisconnectFromServer = false;
}

void NetworkClientAPI::stop()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to stop: not running!");
		return;
	}

	// Close TCP socket
	if (_connectionSocketID != INVALID_SOCKET)
	{
		closesocket(_connectionSocketID);
	}

	// Close UDP socket
	if (_udpMessageSocketID != INVALID_SOCKET)
	{
		closesocket(_udpMessageSocketID);
	}

	// Reset variables
	_connectionSocketID = INVALID_SOCKET;
	_udpMessageSocketID = INVALID_SOCKET;
	_pendingMessages.clear();
	_pingLatencies.clear();
	_lastMilliseconds = 0;
	_username = "";
	_tcpMessageBuild = "";
	_serverIP = "";
	_serverPort = "";
	_isConnectedToServer = false;
	_isConnectingToServer = false;
	_isAcceptedByServer = false;
	_isWaitingForPing = false;
	_mustDisconnectFromServer = false;
	_isRunning = false;
}