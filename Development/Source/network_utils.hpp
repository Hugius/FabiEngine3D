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

	static const string extractIP(SOCKET socket);
	static const string extractIP(sockaddr_in sourceAddress);
	static const string extractPort(SOCKET socket);
	static const string extractPort(sockaddr_in sourceAddress);

	static const bool isMessageReserved(const string& message);

	static inline const string SERVER_PORT = "61205";
	static inline const unsigned int MAX_MESSAGE_BYTES = 512;
	static inline const unsigned int MAX_CLIENT_COUNT = 100;
	static inline const unsigned int IPV4_ADDRESS_LENGTH = 16;
};