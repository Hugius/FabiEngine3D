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

	static const string extractIP(SOCKET socket);
	static const string extractIP(sockaddr_in* address);
	static const string extractPort(SOCKET socket);
	static const string extractPort(sockaddr_in* address);

	static const bool isMessageReady(SOCKET socket);
	static const bool isMessageReserved(const string& message);

	static inline const string SERVER_PORT = "61205";
	static inline const unsigned int MAX_CLIENT_COUNT = 100;
	static inline const unsigned int MAX_MESSAGE_CHARACTERS = 64;
	static inline const unsigned int MAX_USERNAME_CHARACTERS = 16;
	static inline const unsigned int TCP_BUFFER_BYTES = 4096;
	static inline const unsigned int UDP_BUFFER_BYTES = (MAX_USERNAME_CHARACTERS + 1 + MAX_MESSAGE_CHARACTERS);
	static inline const unsigned int IPV4_ADDRESS_LENGTH = 16;
};