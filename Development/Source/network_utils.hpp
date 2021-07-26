#pragma once

#include <string>

using std::string;

// Manually declare SOCKET, because winsock2.h cannot be included in this header
typedef unsigned __int64 SOCKET;

struct sockaddr_in;

class NetworkUtils final
{
public:
	NetworkUtils() = delete;

	static const sockaddr_in composeSocketAddress(const string& IP, const string& port);

	static const string extractSocketAddressIP(sockaddr_in* address);
	static const string extractSocketAddressPort(sockaddr_in* address);
	static const string extractSocketSourceIP(SOCKET socket);
	static const string extractSocketSourcePort(SOCKET socket);
	static const string extractSocketDestinationIP(SOCKET socket);
	static const string extractSocketDestinationPort(SOCKET socket);

	static const bool isValidIP(const string& IP);
	static const bool isUdpMessageReady(SOCKET socket);
	static const bool isMessageReserved(const string& message);

	static inline const string SERVER_PORT = "61205";

	static inline const unsigned int MAX_PING_COUNT = 10;
	static inline const unsigned int MAX_MESSAGE_CHARACTERS = 128;
	static inline const unsigned int MAX_USERNAME_CHARACTERS = 16;
	static inline const unsigned int TCP_BUFFER_BYTES = 4096;
	static inline const unsigned int UDP_BUFFER_BYTES = (MAX_USERNAME_CHARACTERS + 1 + MAX_MESSAGE_CHARACTERS);
	static inline const unsigned int IPV4_ADDRESS_LENGTH = 16;
};