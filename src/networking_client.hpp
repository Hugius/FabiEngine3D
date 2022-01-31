#pragma once

#include "networking_server_message.hpp"

#include <string>
#include <future>
#include <vector>
#include <memory>
#include <tuple>

using std::make_shared;
using std::make_tuple;
using std::string;
using std::vector;
using std::future;
using std::shared_ptr;
using std::tuple;

typedef unsigned __int64 SOCKET;

struct sockaddr_in;

class NetworkingClient final
{
public:
	NetworkingClient();
	~NetworkingClient();

	void start(const string& username);
	void update();
	void connectToServer(const string& serverIP);
	void disconnectFromServer(bool mustBeAccepted);
	void sendTcpMessage(const string& content);
	void sendUdpMessage(const string& content);
	void stop();

	const string& getUsername() const;
	const string& getServerIP() const;

	const unsigned int getPingLatency() const;
	const unsigned int getMaxUsernameSize() const;
	const unsigned int getMaxMessageSize();

	const bool isValidServerIP(const string& serverIP) const;
	const bool isRunning() const;
	const bool isConnectingToServer() const;
	const bool isConnectedToServer() const;
	const bool isAcceptedByServer() const;
	const bool isMessageReserved(const string& message) const;

	const vector<NetworkingServerMessage>& getPendingMessages() const;

private:
	void _setupTcp();
	void _setupUdp();

	static inline const string SERVER_PORT = "61295";
	static inline constexpr unsigned int MAX_PING_COUNT = 10;
	static inline constexpr unsigned int IPV4_ADDRESS_LENGTH = 16;
	static inline constexpr unsigned int MAX_MESSAGE_SIZE = 128;
	static inline constexpr unsigned int MAX_USERNAME_SIZE = 16;
	static inline constexpr unsigned int TCP_BUFFER_BYTES = 4096;
	static inline constexpr unsigned int UDP_BUFFER_BYTES = (MAX_USERNAME_SIZE + 1 + MAX_MESSAGE_SIZE);

	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET socket) const;
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET socket) const;

	const string _extractSocketIP(SOCKET socket) const;
	const string _extractSocketPort(SOCKET socket) const;

	int _waitForServerConnection(SOCKET socket, const string& serverIP) const;
	const string _extractAddressIP(sockaddr_in* address) const;
	const string _extractAddressPort(sockaddr_in* address) const;
	const bool _isMessageReadyUDP(SOCKET socket) const;
	const sockaddr_in _composeSocketAddress(const string& IP, const string& port) const;
	bool _sendTcpMessage(const string& content, bool isReserved, bool mustBeAccepted);
	bool _sendUdpMessage(const string& content, bool isReserved, bool mustBeAccepted) const;
	const bool _isValidIP(const string& IP) const;

	future<tuple<int, int, long long, string>> _tcpMessageThread;
	string _username = "";
	string _serverIP = "";
	string _tcpMessageBuild = "";

	long long _lastMilliseconds = 0;

	future<int> _connectionThread;

	vector<unsigned int> _pingLatencies;

	bool _isRunning = false;
	bool _isConnectingToServer = false;
	bool _isConnectedToServer = false;
	bool _isAcceptedByServer = false;
	bool _isWaitingForPing = false;
	bool _mustDisconnectFromServer = false;

	vector<NetworkingServerMessage> _pendingMessages;
	SOCKET _tcpSocket;
	SOCKET _udpSocket;
};