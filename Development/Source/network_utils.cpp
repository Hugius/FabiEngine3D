#define WIN32_LEAN_AND_MEAN

#include "network_utils.hpp"

#include <ws2tcpip.h>

const sockaddr_in NetworkUtils::composeSocketAddress(const string& IP, const string& port)
{
	sockaddr_in socketAddress = sockaddr_in();
	socketAddress.sin_family = AF_INET;
	InetPton(AF_INET, IP.c_str(), &socketAddress.sin_addr.s_addr);
	socketAddress.sin_port = htons(static_cast<u_short>(stoi(port)));
	return socketAddress;
}

const string NetworkUtils::extractIP(SOCKET socket)
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(socket, (sockaddr*)&socketAddress, &socketAddressLength);
	char IP[IPV4_ADDRESS_LENGTH];
	inet_ntop(AF_INET, &socketAddress.sin_addr, IP, sizeof(IP));
	return string(IP);
}

const string NetworkUtils::extractIP(sockaddr_in* address)
{
	char IP[IPV4_ADDRESS_LENGTH];
	inet_ntop(AF_INET, &(address->sin_addr), IP, sizeof(IP));
	return string(IP);
}

const string NetworkUtils::extractPort(SOCKET socket)
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(socket, (sockaddr*)&socketAddress, &socketAddressLength);
	return std::to_string(ntohs(socketAddress.sin_port));
}

const string NetworkUtils::extractPort(sockaddr_in* address)
{
	return std::to_string(ntohs(address->sin_port));
}

const bool NetworkUtils::isMessageReady(SOCKET socket)
{
	fd_set socketSet = fd_set();
	timeval timeInterval = { 0 , 1 }; // 1 microsecond
	FD_ZERO(&socketSet);
	FD_SET(socket, &socketSet);
	return (select(0, &socketSet, nullptr, nullptr, &timeInterval) > 0);
}

const bool NetworkUtils::isMessageReserved(const string& message)
{
	return
	(
		(message.substr(0, 11) == "SERVER_FULL")			||
		(message.substr(0, 22) == "USER_ALREADY_CONNECTED") ||
		(message.substr(0, 8)  == "ACCEPTED")				||
		(message.substr(0, 4)  == "PING")					||
		(message.substr(0, 22) == "DISCONNECTED_BY_SERVER")
	);
}