#define WIN32_LEAN_AND_MEAN

#include "network_utils.hpp"

#include <ws2tcpip.h>

const string NetworkUtils::extractIP(SOCKET socket)
{
	sockaddr_in socketAddress;
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(socket, (struct sockaddr*)&socketAddress, &socketAddressLength);
	char IP[IPV4_ADDRESS_LENGTH];
	inet_ntop(AF_INET, &socketAddress.sin_addr, IP, sizeof(IP));
	return string(IP);
}

const string NetworkUtils::extractPort(SOCKET socket)
{
	sockaddr_in socketAddress;
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(socket, (struct sockaddr*)&socketAddress, &socketAddressLength);
	return std::to_string(socketAddress.sin_port);
}

const bool NetworkUtils::isMessageReserved(const string& message)
{
	return
		((message == "SERVER_FULL") ||
		(message == "USER_ALREADY_CONNECTED") ||
		(message == "ACCEPTED") ||
		(message == "PING") ||
		(message == "DISCONNECTED_BY_SERVER"));
}