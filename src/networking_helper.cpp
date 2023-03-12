#define WIN32_LEAN_AND_MEAN

#include "networking_helper.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::to_string;

NetworkingHelper::NetworkingHelper()
{
	WSADATA winsockData;

	auto winsockStatus = WSAStartup(MAKEWORD(WINSOCK_MAJOR_VERSION, WINSOCK_MINOR_VERSION), &winsockData);

	if(winsockStatus != 0)
	{
		Logger::throwError("WinSock could not be initialized: ", winsockStatus);
	}
}

NetworkingHelper::~NetworkingHelper()
{
	WSACleanup();
}

const int NetworkingHelper::getMaxUsernameSize() const
{
	return MAX_USERNAME_SIZE;
}

const int NetworkingHelper::getMaxMessageSize() const
{
	return MAX_MESSAGE_SIZE;
}

const bool NetworkingHelper::isMessageReserved(const string & message) const
{
	return _isMessageReserved(message);
}

const string NetworkingHelper::_getSocketIp(SOCKET socket)
{
	sockaddr_in socketAddress = {};

	auto socketAddressLength = static_cast<int>(sizeof(socketAddress));
	auto peerResult = getsockname(socket, (sockaddr *)&socketAddress, &socketAddressLength);

	return _getAddressIp(socketAddress);
}

const string NetworkingHelper::_getSocketPort(SOCKET socket)
{
	sockaddr_in socketAddress = {};

	auto socketAddressLength = static_cast<int>(sizeof(socketAddress));
	auto peerResult = getsockname(socket, (sockaddr *)&socketAddress, &socketAddressLength);

	return _getAddressPort(socketAddress);
}

const string NetworkingHelper::_getPeerIp(SOCKET socket)
{
	sockaddr_in socketAddress = {};

	auto socketAddressLength = static_cast<int>(sizeof(socketAddress));
	auto peerResult = getpeername(socket, (sockaddr *)&socketAddress, &socketAddressLength);

	return _getAddressIp(socketAddress);
}

const string NetworkingHelper::_getPeerPort(SOCKET socket)
{
	sockaddr_in socketAddress = {};

	auto socketAddressLength = static_cast<int>(sizeof(socketAddress));
	auto peerResult = getpeername(socket, (sockaddr *)&socketAddress, &socketAddressLength);

	return _getAddressPort(socketAddress);
}

const sockaddr_in NetworkingHelper::_getSocketAddress(const string & ip, const string & port)
{
	sockaddr_in socketAddress = {};

	socketAddress.sin_family = AF_INET;
	InetPton(AF_INET, ip.c_str(), &socketAddress.sin_addr.s_addr);
	socketAddress.sin_port = htons(static_cast<u_short>(stoi(port)));

	return socketAddress;
}

const string NetworkingHelper::_getAddressIp(sockaddr_in address)
{
	char ip[IP_ADDRESS_SIZE];

	inet_ntop(AF_INET, &(address.sin_addr), ip, sizeof(ip));

	return (ip);
}

const string NetworkingHelper::_getAddressPort(sockaddr_in address)
{
	return to_string(ntohs(address.sin_port));
}

const bool NetworkingHelper::_isUdpMessageReady(SOCKET socket)
{
	fd_set socketSet = {};
	timeval timeInterval = {0, 1};

	FD_ZERO(&socketSet);
	FD_SET(socket, &socketSet);

	return (select(0, &socketSet, nullptr, nullptr, &timeInterval) > 0);
}

const bool NetworkingHelper::_isMessageReserved(const string & message)
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