#pragma once

#include <string>

using std::string;

typedef unsigned __int64 SOCKET;

struct sockaddr_in;

class NetworkingHelper final
{
	friend class NetworkingServer;
	friend class NetworkingClient;

public:
	void initialize();
	void cleanup();

	const int getMaxUsernameSize() const;
	const int getMaxMessageSize() const;

	const bool isMessageReserved(const string & message) const;

private:
	static const string _extractAddressIp(sockaddr_in address);
	static const string _extractAddressPort(sockaddr_in address);
	static const string _extractSocketIp(SOCKET socket);
	static const string _extractSocketPort(SOCKET socket);
	static const string _extractPeerIp(SOCKET socket);
	static const string _extractPeerPort(SOCKET socket);

	static const bool _isUdpMessageReady(SOCKET socket);
	static const bool _isMessageReserved(const string & message);

	static const sockaddr_in _composeSocketAddress(const string & ip, const string & port);

	static inline const string SERVER_PORT = "61295";

	static inline constexpr int WINSOCK_MAJOR_VERSION = 2;
	static inline constexpr int WINSOCK_MINOR_VERSION = 2;
	static inline constexpr int IP_ADDRESS_SIZE = 16;
	static inline constexpr int MAX_USERNAME_SIZE = 16;
	static inline constexpr int MAX_MESSAGE_SIZE = 128;
	static inline constexpr int MAX_TCP_BUFFER_SIZE = 8192;
	static inline constexpr int MAX_UDP_BUFFER_SIZE = (MAX_USERNAME_SIZE + 1 + MAX_MESSAGE_SIZE);
};