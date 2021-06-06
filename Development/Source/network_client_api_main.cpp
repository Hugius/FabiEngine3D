#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkClientAPI::NetworkClientAPI() :
	_tcpSocketID(INVALID_SOCKET),
	_udpSocketID(INVALID_SOCKET)
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

	// Compose TCP address info hints
	addrinfo tcpHints;
	ZeroMemory(&tcpHints, sizeof(tcpHints));
	tcpHints.ai_family = AF_INET; // Ipv4 address
	tcpHints.ai_socktype = SOCK_STREAM; // Streaming socket
	tcpHints.ai_protocol = IPPROTO_TCP; // TCP protocol

	// Compose UDP address info hints
	addrinfo udpHints;
	ZeroMemory(&udpHints, sizeof(udpHints));
	udpHints.ai_family = AF_INET; // Ipv4 address
	udpHints.ai_socktype = SOCK_DGRAM; // Datagram socket
	udpHints.ai_protocol = IPPROTO_UDP; // UDP protocol

	// Create TCP address info
	addrinfo* tcpAddressInfo = nullptr;
	auto tcpInfoStatusCode = getaddrinfo(serverIP.c_str(), serverPort.c_str(), &tcpHints, &tcpAddressInfo);
	if (tcpInfoStatusCode != 0)
	{
		Logger::throwError("Networking client startup (TCP address info) failed with error code: ", tcpInfoStatusCode);
		return;
	}

	// Create UDP address info
	addrinfo* udpAddressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo(serverIP.c_str(), serverPort.c_str(), &udpHints, &udpAddressInfo);
	if (udpInfoStatusCode != 0)
	{
		Logger::throwError("Networking client startup (UDP address info) failed with error code: ", udpInfoStatusCode);
		return;
	}

	// Create TCP socket
	_tcpSocketID = socket(tcpAddressInfo->ai_family, tcpAddressInfo->ai_socktype, tcpAddressInfo->ai_protocol);
	if (_tcpSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking client startup (TCP socket create) failed with error code: ", WSAGetLastError());
	}

	// Create UDP socket
	_udpSocketID = socket(udpAddressInfo->ai_family, udpAddressInfo->ai_socktype, udpAddressInfo->ai_protocol);
	if (_udpSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking client startup (UDP socket create) failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for connecting to the server
	_connectionThread = std::async(std::launch::async, &NetworkClientAPI::_waitForServerConnection, this, _tcpSocketID, serverIP, serverPort);

	// Address infos not needed anymore
	freeaddrinfo(tcpAddressInfo);
	freeaddrinfo(udpAddressInfo);

	// Client is now connecting
	_serverIP = serverIP;
	_serverPort = serverPort;
	_isConnectingToServer = true;
}

void NetworkClientAPI::disconnectFromServer()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to disconnect: not running!");
		return;
	}

	// Must be connected
	if (!_isConnectedToServer)
	{
		Logger::throwWarning("Networking client tried to disconnect: not connected!");
		return;
	}

	// Close server connections
	closesocket(_tcpSocketID);
	closesocket(_udpSocketID);

	// Reset variables
	_tcpSocketID = INVALID_SOCKET;
	_udpSocketID = INVALID_SOCKET;
	_pendingMessages.clear();
	_pingLatencies.clear();
	_lastMilliseconds = 0;
	_currentTcpMessageBuild = "";
	_serverIP = "";
	_serverPort = "";
	_isConnectedToServer = false;
	_isAcceptedByServer = false;
	_isWaitingForPing = false;
}

void NetworkClientAPI::stop()
{
	// Must be running
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