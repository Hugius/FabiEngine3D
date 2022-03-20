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
	void sendTcpMessageToClient(const string& username, const string& content);
	void sendUdpMessageToClient(const string& username, const string& content);
	void broadcastTcpMessageToClients(const string& content);
	void broadcastUdpMessageToClients(const string& content);
	void disconnectClient(const string& username);
	void disconnectClients();
	void stop();

	const vector<string> getClientIps() const;
	const vector<string> getClientUsernames() const;
	const vector<NetworkingClientMessage>& getPendingMessages() const;

	const string getNewClientIp() const;
	const string getNewClientUsername() const;
	const string getOldClientIp() const;
	const string getOldClientUsername() const;

	const unsigned int getMaxMessageSize() const;

	const bool isRunning() const;
	const bool isClientConnected(const string& username) const;
	const bool isMessageReserved(const string& message) const;

private:
	void _disconnectClient(SOCKET socket);

	const tuple<int, int, long long, string> _waitForTcpMessage(SOCKET socket) const;
	const tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET socket) const;

	const string _extractPeerIp(SOCKET socket) const;
	const string _extractPeerPort(SOCKET socket) const;
	const string _extractAddressIp(sockaddr_in* address) const;
	const string _extractAddressPort(sockaddr_in* address) const;

	const bool _sendTcpMessageToClient(SOCKET socket, const string& content, bool isReserved);
	const bool _sendUdpMessageToClient(const string& clientIp, const string& clientPort, const string& content, bool isReserved) const;
	const bool _isMessageReadyUDP(SOCKET socket) const;

	const SOCKET _waitForClientConnection(SOCKET socket) const;
	const sockaddr_in _composeSocketAddress(const string& ip, const string& port) const;

	static inline const string SERVER_PORT = "61295";
	static inline constexpr unsigned int PORT_DIGIT_COUNT = 5;
	static inline constexpr unsigned int IPV4_ADDRESS_LENGTH = 16;
	static inline constexpr unsigned int MAX_MESSAGE_SIZE = 128;
	static inline constexpr unsigned int MAX_USERNAME_SIZE = 16;
	static inline constexpr unsigned int TCP_BUFFER_BYTES = 4096;
	static inline constexpr unsigned int UDP_BUFFER_BYTES = (MAX_USERNAME_SIZE + 1 + MAX_MESSAGE_SIZE);

	vector<future<tuple<int, int, long long, string>>> _tcpMessageThreads = {};
	vector<string> _tcpMessageBuilds = {};
	vector<string> _clientIps = {};
	vector<string> _tcpClientPorts = {};
	vector<string> _udpClientPorts = {};
	vector<string> _clientUsernames = {};
	vector<string> _oldClientIps = {};
	vector<string> _oldClientUsernames = {};
	vector<NetworkingClientMessage> _pendingMessages = {};
	vector<SOCKET> _clientSockets = {};

	string _newClientIp = "";
	string _newClientUsername = "";

	unsigned int _maxClientCount = 0;

	bool _isRunning = false;

	SOCKET _tcpSocket;
	SOCKET _udpSocket;

	future<SOCKET> _connectionThread;
};