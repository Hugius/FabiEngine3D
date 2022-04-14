#include "networking_server.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <ws2tcpip.h>

using std::to_string;

const bool NetworkingServer::_sendTcpMessageToClient(SOCKET socket, const string & content, bool isReserved)
{
	if(!_isRunning)
	{
		abort();
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}
	if(isMessageReserved(content) && !isReserved)
	{
		abort();
	}
	if(content.size() > MAX_MESSAGE_SIZE)
	{
		abort();
	}

	string message = (content + ';');

	auto sendStatusCode = send(socket, message.c_str(), static_cast<int>(message.size()), 0);

	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
		{
			_disconnectClient(socket);
			return false;
		}
		else if(WSAGetLastError() == WSAENOBUFS)
		{
			Logger::throwInfo("Networking server is sending too many TCP messages");
		}
		else
		{
			Logger::throwDebug(WSAGetLastError());
			abort();
		}
	}

	return true;
}

const bool NetworkingServer::_sendUdpMessageToClient(const string & clientIp, const string & clientPort, const string & content, bool isReserved) const
{
	if(!_isRunning)
	{
		abort();
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}
	if(isMessageReserved(content) && !isReserved)
	{
		abort();
	}
	if(content.size() > MAX_MESSAGE_SIZE)
	{
		abort();
	}

	auto socketAddress = _composeSocketAddress(clientIp, clientPort);

	auto sendStatusCode = sendto(_udpSocket, content.c_str(), static_cast<int>(content.size()), 0, reinterpret_cast<sockaddr *>(&socketAddress), sizeof(socketAddress));

	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAENOBUFS)
		{
			Logger::throwInfo("Networking server is sending too many UDP messages");
		}
		else
		{
			Logger::throwDebug(WSAGetLastError());
			abort();
		}
	}

	return true;
}

const bool NetworkingServer::_setupTcp()
{
	addrinfo tcpHints = addrinfo();
	ZeroMemory(&tcpHints, sizeof(tcpHints));
	tcpHints.ai_family = AF_INET;
	tcpHints.ai_socktype = SOCK_STREAM;
	tcpHints.ai_protocol = IPPROTO_TCP;

	addrinfo * tcpAddressInfo = nullptr;
	auto tcpInfoStatusCode = getaddrinfo("0.0.0.0", SERVER_PORT.c_str(), &tcpHints, &tcpAddressInfo);
	if(tcpInfoStatusCode != 0)
	{
		Logger::throwDebug(tcpInfoStatusCode);
		abort();
	}

	_tcpSocket = socket(tcpAddressInfo->ai_family, tcpAddressInfo->ai_socktype, tcpAddressInfo->ai_protocol);
	if(_tcpSocket == INVALID_SOCKET)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	DWORD trueValue = 1;
	DWORD falseValue = 0;
	setsockopt(_tcpSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<char *>(&trueValue), sizeof(trueValue));
	setsockopt(_tcpSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&falseValue), sizeof(falseValue));

	auto tcpBindStatusCode = bind(_tcpSocket, tcpAddressInfo->ai_addr, static_cast<int>(tcpAddressInfo->ai_addrlen));
	if(tcpBindStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAEADDRINUSE)
		{
			Logger::throwInfo("Current machine is already hosting a networking server");
			freeaddrinfo(tcpAddressInfo);
			return false;
		}
		else
		{
			Logger::throwDebug(WSAGetLastError());
			abort();
		}
	}

	auto listenStatusCode = listen(_tcpSocket, SOMAXCONN);
	if(listenStatusCode == SOCKET_ERROR)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	freeaddrinfo(tcpAddressInfo);

	return true;
}

const bool NetworkingServer::_setupUdp()
{
	addrinfo udpHints = addrinfo();
	ZeroMemory(&udpHints, sizeof(udpHints));
	udpHints.ai_family = AF_INET;
	udpHints.ai_socktype = SOCK_DGRAM;
	udpHints.ai_protocol = IPPROTO_UDP;

	addrinfo * udpAddressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo("0.0.0.0", SERVER_PORT.c_str(), &udpHints, &udpAddressInfo);
	if(udpInfoStatusCode != 0)
	{
		Logger::throwDebug(udpInfoStatusCode);
		abort();
	}

	_udpSocket = socket(udpAddressInfo->ai_family, udpAddressInfo->ai_socktype, udpAddressInfo->ai_protocol);
	if(_udpSocket == INVALID_SOCKET)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	DWORD trueValue = 1;
	DWORD falseValue = 0;
	setsockopt(_udpSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, reinterpret_cast<char *>(&trueValue), sizeof(trueValue));
	setsockopt(_udpSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&falseValue), sizeof(falseValue));

	auto udpBindStatusCode = bind(_udpSocket, udpAddressInfo->ai_addr, static_cast<int>(udpAddressInfo->ai_addrlen));
	if(udpBindStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAEADDRINUSE)
		{
			Logger::throwInfo("Current machine is already hosting a networking server");
			freeaddrinfo(udpAddressInfo);
			return false;
		}
		else
		{
			Logger::throwDebug(WSAGetLastError());
			abort();
		}
	}

	freeaddrinfo(udpAddressInfo);

	return true;
}

void NetworkingServer::_disconnectClient(SOCKET socket)
{
	for(unsigned int index = 0; index < static_cast<unsigned int>(_clientSockets.size()); index++)
	{
		if(socket == _clientSockets[index])
		{
			auto clientUsername = _clientUsernames[index];

			closesocket(socket);

			_oldClientIps.push_back(_clientIps[index]);
			_oldClientUsernames.push_back(_clientUsernames[index]);

			_clientSockets.erase(_clientSockets.begin() + index);
			_clientIps.erase(_clientIps.begin() + index);
			_tcpClientPorts.erase(_tcpClientPorts.begin() + index);
			_udpClientPorts.erase(_udpClientPorts.begin() + index);
			_clientUsernames.erase(_clientUsernames.begin() + index);
			_tcpMessageBuilds.erase(_tcpMessageBuilds.begin() + index);
			_tcpMessageThreads.erase(_tcpMessageThreads.begin() + index);

			if(!clientUsername.empty())
			{
				Logger::throwInfo("Networking client \"" + clientUsername + "\" disconnected from the server");
			}

			return;
		}
	}
}

const SOCKET NetworkingServer::_waitForClientConnection(SOCKET socket) const
{
	return accept(socket, nullptr, nullptr);
}

tuple<int, int, long long, string> NetworkingServer::_waitForTcpMessage(SOCKET socket) const
{
	char buffer[TCP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(TCP_BUFFER_BYTES);
	auto receiveStatusCode = recv(socket, buffer, bufferLength, 0);

	if(receiveStatusCode > 0)
	{
		return make_tuple(receiveStatusCode, 0, Tools::getTimeSinceEpochMS(), string(buffer, receiveStatusCode));
	}
	else if(receiveStatusCode == 0)
	{
		return make_tuple(receiveStatusCode, 0, Tools::getTimeSinceEpochMS(), "");
	}
	else
	{
		return make_tuple(receiveStatusCode, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, string, string, string> NetworkingServer::_receiveUdpMessage(SOCKET socket) const
{
	char buffer[UDP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(UDP_BUFFER_BYTES);
	sockaddr_in sourceAddress = sockaddr_in();
	int sourceAddressLength = sizeof(sourceAddress);

	auto receiveResult = recvfrom(socket, buffer, bufferLength, 0, reinterpret_cast<sockaddr *>(&sourceAddress), &sourceAddressLength);

	auto ip = _extractAddressIp(&sourceAddress);
	auto port = _extractAddressPort(&sourceAddress);

	if(receiveResult > 0)
	{
		return make_tuple(receiveResult, WSAGetLastError(), string(buffer, receiveResult), ip, port);
	}
	else
	{
		return make_tuple(receiveResult, WSAGetLastError(), "", ip, port);
	}
}

const string NetworkingServer::_extractPeerIp(SOCKET socket) const
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(socket, (sockaddr *)&socketAddress, &socketAddressLength);

	return _extractAddressIp(&socketAddress);
}

const string NetworkingServer::_extractPeerPort(SOCKET socket) const
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(socket, (sockaddr *)&socketAddress, &socketAddressLength);

	return _extractAddressPort(&socketAddress);
}

const sockaddr_in NetworkingServer::_composeSocketAddress(const string & ip, const string & port) const
{
	sockaddr_in socketAddress = sockaddr_in();
	socketAddress.sin_family = AF_INET;
	InetPton(AF_INET, ip.c_str(), &socketAddress.sin_addr.s_addr);
	socketAddress.sin_port = htons(static_cast<u_short>(stoi(port)));

	return socketAddress;
}

const string NetworkingServer::_extractAddressIp(sockaddr_in * address) const
{
	char ip[IPV4_ADDRESS_LENGTH];
	inet_ntop(AF_INET, &(address->sin_addr), ip, sizeof(ip));

	return (ip);
}

const string NetworkingServer::_extractAddressPort(sockaddr_in * address) const
{
	return to_string(ntohs(address->sin_port));
}

const bool NetworkingServer::_isMessageReadyUDP(SOCKET socket) const
{
	fd_set socketSet = fd_set();
	timeval timeInterval = {0, 1};
	FD_ZERO(&socketSet);
	FD_SET(socket, &socketSet);

	return (select(0, &socketSet, nullptr, nullptr, &timeInterval) > 0);
}

const bool NetworkingServer::isMessageReserved(const string & message) const
{
	return
		(
		(message.substr(0, string("REQUEST").size()) == "REQUEST") ||
		(message.substr(0, string("ACCEPT").size()) == "ACCEPT") ||
		(message.substr(0, string("PING").size()) == "PING") ||
		(message.substr(0, string("SERVER_FULL").size()) == "SERVER_FULL") ||
		(message.substr(0, string("ALREADY_CONNECTED").size()) == "ALREADY_CONNECTED") ||
		(message.substr(0, string("DISCONNECTED").size()) == "DISCONNECTED")
		);
}