#define WIN32_LEAN_AND_MEAN

#include "networking_client.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <ws2tcpip.h>

using std::launch;
using std::to_string;

bool NetworkingClient::_sendTcpMessageToServer(const string& content, bool isReserved, bool mustBeAccepted)
{
	if(!_isRunning)
	{
		abort();
	}
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
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

	auto sendStatusCode = send(_tcpSocket, message.c_str(), static_cast<int>(message.size()), 0);

	if(sendStatusCode == SOCKET_ERROR)
	{
		if((WSAGetLastError() == WSAECONNRESET) || (WSAGetLastError() == WSAECONNABORTED))
		{
			disconnectFromServer(mustBeAccepted);
			return false;
		}
		else if(WSAGetLastError() == WSAENOBUFS)
		{
			Logger::throwWarning("Networking client is sending too many TCP messages");
		}
		else
		{
			Logger::throwDebug(WSAGetLastError());
			abort();
		}
	}

	return true;
}

bool NetworkingClient::_sendUdpMessageToServer(const string& content, bool isReserved, bool mustBeAccepted) const
{
	if(!_isRunning)
	{
		abort();
	}
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
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

	auto socketAddress = _composeSocketAddress(_serverIp, SERVER_PORT);

	string message = (_username + ';' + content);

	auto sendStatusCode = sendto(
		_udpSocket,
		message.c_str(),
		static_cast<int>(message.size()),
		0,
		reinterpret_cast<sockaddr*>(&socketAddress),
		sizeof(socketAddress));

	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAENOBUFS)
		{
			Logger::throwWarning("Networking client is sending too many UDP messages");
		}
		else
		{
			Logger::throwDebug(WSAGetLastError());
			abort();
		}
	}

	return true;
}

int NetworkingClient::_waitForServerConnection(SOCKET socket, const string& ip) const
{
	auto socketAddress = _composeSocketAddress(ip, SERVER_PORT);

	auto connectStatusCode = connect(socket, reinterpret_cast<sockaddr*>(&socketAddress), sizeof(socketAddress));

	if(connectStatusCode == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}
	else
	{
		return 0;
	}
}

void NetworkingClient::_setupTcp()
{
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	addrinfo* addressInfo = nullptr;
	auto tcpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);
	if(tcpInfoStatusCode != 0)
	{
		Logger::throwDebug(tcpInfoStatusCode);
		abort();
	}

	_tcpSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_tcpSocket == INVALID_SOCKET)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	auto tcpBindStatusCode = bind(_tcpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(tcpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	freeaddrinfo(addressInfo);

	_connectionThread = async(launch::async, &NetworkingClient::_waitForServerConnection, this, _tcpSocket, _serverIp);
}

void NetworkingClient::_setupUdp()
{
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	addrinfo* addressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);
	if(udpInfoStatusCode != 0)
	{
		Logger::throwDebug(udpInfoStatusCode);
		abort();
	}

	_udpSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_udpSocket == INVALID_SOCKET)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	auto udpBindStatusCode = bind(_udpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(udpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	freeaddrinfo(addressInfo);
}

tuple<int, int, long long, string> NetworkingClient::_waitForTcpMessage(SOCKET socket) const
{
	char buffer[TCP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(TCP_BUFFER_BYTES);
	auto receiveResult = recv(socket, buffer, bufferLength, 0);

	if(receiveResult > 0)
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), string(buffer, receiveResult));
	}
	else
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, string, string, string> NetworkingClient::_receiveUdpMessage(SOCKET socket) const
{
	char buffer[UDP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(UDP_BUFFER_BYTES);
	sockaddr_in sourceAddress = sockaddr_in();
	int sourceAddressLength = sizeof(sourceAddress);

	auto receiveResult = recvfrom(socket, buffer, bufferLength, 0, reinterpret_cast<sockaddr*>(&sourceAddress), &sourceAddressLength);

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

const string NetworkingClient::_extractSocketIp(SOCKET socket) const
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getsockname(socket, (sockaddr*)&socketAddress, &socketAddressLength);

	return _extractAddressIp(&socketAddress);
}

const string NetworkingClient::_extractSocketPort(SOCKET socket) const
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getsockname(socket, (sockaddr*)&socketAddress, &socketAddressLength);

	return _extractAddressPort(&socketAddress);
}

const sockaddr_in NetworkingClient::_composeSocketAddress(const string& ip, const string& port) const
{
	sockaddr_in socketAddress = sockaddr_in();
	socketAddress.sin_family = AF_INET;
	InetPton(AF_INET, ip.c_str(), &socketAddress.sin_addr.s_addr);
	socketAddress.sin_port = htons(static_cast<u_short>(stoi(port)));

	return socketAddress;
}

const string NetworkingClient::_extractAddressIp(sockaddr_in* address) const
{
	char ip[IPV4_ADDRESS_LENGTH];

	inet_ntop(AF_INET, &(address->sin_addr), ip, sizeof(ip));

	return string(ip);
}

const string NetworkingClient::_extractAddressPort(sockaddr_in* address) const
{
	return to_string(ntohs(address->sin_port));
}

const bool NetworkingClient::_isMessageReadyUDP(SOCKET socket) const
{
	fd_set socketSet = fd_set();
	timeval timeInterval = {0, 1};
	FD_ZERO(&socketSet);
	FD_SET(socket, &socketSet);

	return (select(0, &socketSet, nullptr, nullptr, &timeInterval) > 0);
}

const bool NetworkingClient::isMessageReserved(const string& message) const
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