#define WIN32_LEAN_AND_MEAN

#include "network_server_api.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkServerAPI::NetworkServerAPI()
	:
	_connectionSocketID(INVALID_SOCKET),
	_udpMessageSocketID(INVALID_SOCKET),
	_maxClientCount(0),
	_newClientIP(""),
	_newClientPort(""),
	_newClientUsername(""),
	_isRunning(false)
{

}

NetworkServerAPI::~NetworkServerAPI()
{
	if (_isRunning)
	{
		stop();
	}
}

void NetworkServerAPI::start(unsigned int maxClientCount)
{
	// Must not be running
	if (_isRunning)
	{
		Logger::throwWarning("Networking server tried to start: already running!");
		return;
	}

	// Validate custom client count
	if (maxClientCount <= 0)
	{
		Logger::throwWarning("Networking server tried to start: invalid maximum client count!");
		return;
	}

	// Compose TCP address info hints
	addrinfo tcpHints = addrinfo();
	ZeroMemory(&tcpHints, sizeof(tcpHints));
	tcpHints.ai_family = AF_INET; // Ipv4 address
	tcpHints.ai_socktype = SOCK_STREAM; // Streaming socket
	tcpHints.ai_protocol = IPPROTO_TCP; // TCP protocol
	tcpHints.ai_flags = AI_PASSIVE; // Flag to indicate the current machines's IPV4 should be used

	// Compose UDP address info hints
	addrinfo udpHints = addrinfo();
	ZeroMemory(&udpHints, sizeof(udpHints));
	udpHints.ai_family = AF_INET; // Ipv4 address
	udpHints.ai_socktype = SOCK_DGRAM; // Datagram socket
	udpHints.ai_protocol = IPPROTO_UDP; // UDP protocol
	udpHints.ai_flags = AI_PASSIVE; // Flag to indicate the current machines's IPV4 should be used

	// Create TCP address info
	addrinfo* tcpAddressInfo = nullptr;
	auto tcpInfoStatusCode = getaddrinfo(nullptr, NetworkUtils::SERVER_PORT.c_str(), &tcpHints, &tcpAddressInfo);
	if (tcpInfoStatusCode != 0)
	{
		Logger::throwError("Networking server TCP address info failed with error code: ", tcpInfoStatusCode);
	}

	// Create UDP address info
	addrinfo* udpAddressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo(nullptr, NetworkUtils::SERVER_PORT.c_str(), &udpHints, &udpAddressInfo);
	if (udpInfoStatusCode != 0)
	{
		Logger::throwError("Networking server UDP address info failed with error code: ", udpInfoStatusCode);
	}

	// Create socket for listening to client connection requests
	_connectionSocketID = socket(tcpAddressInfo->ai_family, tcpAddressInfo->ai_socktype, tcpAddressInfo->ai_protocol);
	if (_connectionSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking server TCP socket create failed with error code: ", WSAGetLastError());
	}

	// Add options to connection socket
	DWORD optionValue = 1;
	setsockopt(_connectionSocketID, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&optionValue), sizeof(optionValue));

	// Create socket for handling UDP messages
	_udpMessageSocketID = socket(udpAddressInfo->ai_family, udpAddressInfo->ai_socktype, udpAddressInfo->ai_protocol);
	if (_udpMessageSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking server UDP socket create failed with error code: ", WSAGetLastError());
	}

	// Bind connection socket
	auto tcpBindStatusCode = bind(_connectionSocketID, tcpAddressInfo->ai_addr, static_cast<int>(tcpAddressInfo->ai_addrlen));
	if (tcpBindStatusCode == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEADDRINUSE) // Server already running on current machine
		{
			Logger::throwWarning("Networking server tried to start: current machine already hosting a server!");
			freeaddrinfo(tcpAddressInfo);
			freeaddrinfo(udpAddressInfo);
			return;
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking server TCP socket bind failed with error code: ", WSAGetLastError());
		}
	}

	// Bind UDP message socket
	auto udpBindStatusCode = bind(_udpMessageSocketID, udpAddressInfo->ai_addr, static_cast<int>(udpAddressInfo->ai_addrlen));
	if (udpBindStatusCode == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEADDRINUSE) // Server already running on current machine
		{
			Logger::throwWarning("Networking server tried to start: current machine already hosting a server!");
			freeaddrinfo(tcpAddressInfo);
			freeaddrinfo(udpAddressInfo);
			return;
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking server UDP socket bind failed with error code: ", WSAGetLastError());
		}
	}

	// Enable listening for any incoming connection requests
	auto listenStatusCode = listen(_connectionSocketID, SOMAXCONN);
	if (listenStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking server TCP socket listen failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for accepting incoming connection requests
	_connectionThread = std::async(std::launch::async, &NetworkServerAPI::_waitForClientConnection, this, _connectionSocketID);

	// Address infos not needed anymore
	freeaddrinfo(tcpAddressInfo);
	freeaddrinfo(udpAddressInfo);

	// Server is now operable
	_maxClientCount = maxClientCount;
	_isRunning = true;

	// Logging
	Logger::throwInfo("Started networking server!");
}

void NetworkServerAPI::stop()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to stop: not running!");
		return;
	}

	// Close TCP connection socket
	closesocket(_connectionSocketID);

	// Close UDP message socket
	closesocket(_udpMessageSocketID);

	// Delete all connected clients
BEGIN:
	for (const auto& socketID : _clientSocketIDs)
	{
		_disconnectClient(socketID);
		goto BEGIN;
	}

	// Miscellaneous
	_pendingMessages.clear();
	_tcpMessageThreads.clear();
	_connectionSocketID = INVALID_SOCKET;
	_udpMessageSocketID = INVALID_SOCKET;
	_maxClientCount = 0;
	_newClientUsername = "";
	_isRunning = false;

	// Logging
	Logger::throwInfo("Stopped networking server!");
}