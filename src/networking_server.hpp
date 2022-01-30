#pragma once

#include "networking_client_message.hpp"

#include <future>
#include <vector>
#include <memory>
#include <tuple>

using std::make_shared;
using std::make_tuple;
using std::vector;
using std::future;
using std::shared_ptr;
using std::tuple;

typedef unsigned __int64 SOCKET;

struct sockaddr_in;

class NetworkingServer final
{
public:
	NetworkingServer();
	~NetworkingServer();

	void start(unsigned int maxClientCount);
	void update();
	void sendTcpMessage(const string& username, const string& content);
	void sendUdpMessage(const string& username, const string& content);
	void broadcastTcpMessage(const string& content, const string& exceptionUsername);
	void broadcastUdpMessage(const string& content, const string& exceptionUsername);
	void disconnectClient(const string& username);
	void disconnectClients();
	void stop();

	const vector<string> getClientIPs() const;
	const vector<string> getClientUsernames() const;
	const string getNewClientIP() const;
	const string getNewClientUsername() const;
	const string getOldClientIP() const;
	const string getOldClientUsername() const;

	const bool isRunning() const;
	const bool isClientConnected(const string& username) const;

	const vector<NetworkingClientMessage>& getPendingMessages() const;

private:
	void _disconnectClient(SOCKET socket);

	static inline const string SERVER_PORT = "61295";
	static inline constexpr unsigned int PORT_DIGIT_COUNT = 5;
	static inline constexpr unsigned int IPV4_ADDRESS_LENGTH = 16;
	static inline constexpr unsigned int MAX_MESSAGE_CHARACTERS = 128;
	static inline constexpr unsigned int MAX_USERNAME_CHARACTERS = 16;
	static inline constexpr unsigned int TCP_BUFFER_BYTES = 4096;
	static inline constexpr unsigned int UDP_BUFFER_BYTES = (MAX_USERNAME_CHARACTERS + 1 + MAX_MESSAGE_CHARACTERS);

	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET socket) const;
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET socket) const;

	const string _extractPeerIP(SOCKET socket);
	const string _extractPeerPort(SOCKET socket);

	const bool _sendTcpMessage(SOCKET socket, const string& content, bool isReserved);
	const bool _sendUdpMessage(const string& clientIP, const string& clientPort, const string& content, bool isReserved) const;

	const SOCKET _waitForClientConnection(SOCKET socket) const;

	const string _extractAddressIP(sockaddr_in* address) const;
	const string _extractAddressPort(sockaddr_in* address) const;
	const bool _isMessageReadyUDP(SOCKET socket) const;
	const bool _isMessageReserved(const string& message) const;
	const sockaddr_in _composeSocketAddress(const string& IP, const string& port) const;

	vector<future<tuple<int, int, long long, string>>> _tcpMessageThreads;
	vector<string> _tcpMessageBuilds;
	vector<string> _clientIPs;
	vector<string> _tcpClientPorts;
	vector<string> _udpClientPorts;
	vector<string> _clientUsernames;
	vector<string> _oldClientIPs;
	vector<string> _oldClientUsernames;
	string _newClientIP = "";
	string _newClientUsername = "";

	unsigned int _maxClientCount = 0;

	bool _isRunning = false;

	vector<NetworkingClientMessage> _pendingMessages;
	vector<SOCKET> _clientSockets;
	future<SOCKET> _connectionThread;
	SOCKET _tcpSocket;
	SOCKET _udpSocket;
};