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

	// Strings
	static const string extractAddressIP(sockaddr_in* address);
	static const string extractAddressPort(sockaddr_in* address);
	static const string extractSocketIP(SOCKET socket);
	static const string extractSocketPort(SOCKET socket);
	static const string extractPeerIP(SOCKET socket);
	static const string extractPeerPort(SOCKET socket);

	// Booleans
	static const bool isValidIP(const string& IP);
	static const bool isMessageReadyUDP(SOCKET socket);
	static const bool isMessageReserved(const string& message);

	// Miscellaneous
	static const sockaddr_in composeSocketAddress(const string& IP, const string& port);

	// Strings
	static inline const string SERVER_PORT = "61295";

	// Integers
	static inline const unsigned int PORT_DIGIT_COUNT = 5;
	static inline const unsigned int MAX_PING_COUNT = 10;
	static inline const unsigned int MAX_MESSAGE_CHARACTERS = 128;
	static inline const unsigned int MAX_USERNAME_CHARACTERS = 16;
	static inline const unsigned int TCP_BUFFER_BYTES = 4096;
	static inline const unsigned int UDP_BUFFER_BYTES = (MAX_USERNAME_CHARACTERS + 1 + MAX_MESSAGE_CHARACTERS);
	static inline const unsigned int IPV4_ADDRESS_LENGTH = 16;
};