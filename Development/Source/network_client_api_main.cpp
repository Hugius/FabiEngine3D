#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkClientAPI::NetworkClientAPI() :
	_tcpServerSocketID(INVALID_SOCKET),
	_udpServerSocketID(INVALID_SOCKET)
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
	_tcpServerSocketID = socket(tcpAddressInfo->ai_family, tcpAddressInfo->ai_socktype, tcpAddressInfo->ai_protocol);
	if (_tcpServerSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking client startup (TCP socket create) failed with error code: ", WSAGetLastError());
	}

	// Create UDP socket
	_udpServerSocketID = socket(udpAddressInfo->ai_family, udpAddressInfo->ai_socktype, udpAddressInfo->ai_protocol);
	if (_udpServerSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking client startup (UDP socket create) failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for connecting to the server
	_connectionThread = std::async(std::launch::async, &NetworkClientAPI::_waitForServerConnection, this, _tcpServerSocketID, serverIP, serverPort);

	// Address infos not needed anymore
	freeaddrinfo(tcpAddressInfo);
	freeaddrinfo(udpAddressInfo);

	// Client is now connecting
	_isConnectingToServer = true;
	_serverIP = serverIP;
	_serverPort = serverPort;
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
	closesocket(_tcpServerSocketID);
	closesocket(_udpServerSocketID);

	// Reset variables
	_tcpServerSocketID = INVALID_SOCKET;
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