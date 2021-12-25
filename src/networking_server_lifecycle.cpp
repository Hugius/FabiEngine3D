#define WIN32_LEAN_AND_MEAN

#include "networking_server.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::launch;

NetworkingServer::NetworkingServer()
	:
	_tcpSocket(INVALID_SOCKET),
	_udpSocket(INVALID_SOCKET)
{

}

NetworkingServer::~NetworkingServer()
{
	if(_isRunning)
	{
		stop();
	}
}

void NetworkingServer::start(unsigned int maxClientCount)
{
	if(_isRunning)
	{
		Logger::throwError("NetworkingServer::start::1");
	}

	if(maxClientCount <= 0)
	{
		Logger::throwError("NetworkingServer::start::2");
	}

	addrinfo tcpHints = addrinfo();
	ZeroMemory(&tcpHints, sizeof(tcpHints));
	tcpHints.ai_family = AF_INET; // Ipv4 address
	tcpHints.ai_socktype = SOCK_STREAM; // Streaming socket
	tcpHints.ai_protocol = IPPROTO_TCP; // TCP protocol

	addrinfo udpHints = addrinfo();
	ZeroMemory(&udpHints, sizeof(udpHints));
	udpHints.ai_family = AF_INET; // Ipv4 address
	udpHints.ai_socktype = SOCK_DGRAM; // Datagram socket
	udpHints.ai_protocol = IPPROTO_UDP; // UDP protocol

	addrinfo* tcpAddressInfo = nullptr;
	auto tcpInfoStatusCode = getaddrinfo("0.0.0.0", NetworkingUtils::SERVER_PORT.c_str(), &tcpHints, &tcpAddressInfo);
	if(tcpInfoStatusCode != 0)
	{
		Logger::throwError("NetworkingServer::start::3 ---> ", tcpInfoStatusCode);
	}

	addrinfo* udpAddressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo("0.0.0.0", NetworkingUtils::SERVER_PORT.c_str(), &udpHints, &udpAddressInfo);
	if(udpInfoStatusCode != 0)
	{
		Logger::throwError("NetworkingServer::start::4 ---> ", udpInfoStatusCode);
	}

	_tcpSocket = socket(tcpAddressInfo->ai_family, tcpAddressInfo->ai_socktype, tcpAddressInfo->ai_protocol);
	if(_tcpSocket == INVALID_SOCKET)
	{
		Logger::throwError("NetworkingServer::start::5 ---> ", WSAGetLastError());
	}

	_udpSocket = socket(udpAddressInfo->ai_family, udpAddressInfo->ai_socktype, udpAddressInfo->ai_protocol);
	if(_udpSocket == INVALID_SOCKET)
	{
		Logger::throwError("NetworkingServer::start::6 ---> ", WSAGetLastError());
	}

	DWORD trueValue = 1;
	DWORD falseValue = 0;
	setsockopt(_tcpSocket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&trueValue), sizeof(trueValue));
	setsockopt(_tcpSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<char*>(&trueValue), sizeof(trueValue));
	setsockopt(_udpSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<char*>(&trueValue), sizeof(trueValue));
	setsockopt(_tcpSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&falseValue), sizeof(falseValue));
	setsockopt(_udpSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&falseValue), sizeof(falseValue));

	auto tcpBindStatusCode = bind(_tcpSocket, tcpAddressInfo->ai_addr, static_cast<int>(tcpAddressInfo->ai_addrlen));
	if(tcpBindStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAEADDRINUSE) // Server already running on current machine
		{
			Logger::throwWarning("Networking server tried to start: current machine already hosting a server!");
			freeaddrinfo(tcpAddressInfo);
			freeaddrinfo(udpAddressInfo);
			return;
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkingServer::start::7 ---> ", WSAGetLastError());
		}
	}

	auto udpBindStatusCode = bind(_udpSocket, udpAddressInfo->ai_addr, static_cast<int>(udpAddressInfo->ai_addrlen));
	if(udpBindStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAEADDRINUSE) // Server already running on current machine
		{
			Logger::throwWarning("Networking server tried to start: current machine already hosting a server!");
			freeaddrinfo(tcpAddressInfo);
			freeaddrinfo(udpAddressInfo);
			return;
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkingServer::start::8 ---> ", WSAGetLastError());
		}
	}

	auto listenStatusCode = listen(_tcpSocket, SOMAXCONN);
	if(listenStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("NetworkingServer::start::9 ---> ", WSAGetLastError());
	}

	_connectionThread = async(launch::async, &NetworkingServer::_waitForClientConnection, this, _tcpSocket);

	freeaddrinfo(tcpAddressInfo);
	freeaddrinfo(udpAddressInfo);

	_maxClientCount = maxClientCount;
	_isRunning = true;

	Logger::throwInfo("Started networking server!");
}

void NetworkingServer::stop()
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::stop");
	}

	closesocket(_tcpSocket);

	closesocket(_udpSocket);

	BEGIN:;
	for(const auto& socketID : _clientSockets)
	{
		_disconnectClient(socketID);
		goto BEGIN;
	}

	_pendingMessages.clear();
	_tcpSocket = INVALID_SOCKET;
	_udpSocket = INVALID_SOCKET;
	_maxClientCount = 0;
	_newClientIP = "";
	_newClientUsername = "";
	_isRunning = false;

	Logger::throwInfo("Stopped networking server!");
}