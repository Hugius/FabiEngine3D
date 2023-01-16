#pragma once

#include "networking_server_message.hpp"
#include "networking_helper.hpp"

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

class NetworkingClient final
{
public:
	NetworkingClient();
	~NetworkingClient();

	void start(const string & username);
	void update();
	void connectToServer(const string & ip);
	void disconnectFromServer(bool mustBeAccepted);
	void sendTcpMessageToServer(const string & content);
	void sendUdpMessageToServer(const string & content);
	void stop();

	const vector<NetworkingServerMessage> & getPendingMessages() const;

	const string & getUsername() const;
	const string & getServerIp() const;

	const int getPingLatency() const;

	const bool isValidIp(const string & ip) const;
	const bool isRunning() const;
	const bool isConnectingToServer() const;
	const bool isConnectedToServer() const;
	const bool isAcceptedByServer() const;

private:
	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET socket) const;
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET socket) const;

	const int _waitForServerConnection(SOCKET socket, const string & ip) const;

	const bool _setupTcp();
	const bool _setupUdp();
	const bool _sendTcpMessageToServer(const string & content, bool isReserved, bool mustBeAccepted);
	const bool _sendUdpMessageToServer(const string & content, bool isReserved, bool mustBeAccepted) const;

	static inline constexpr int MAX_PING_COUNT = 10;

	vector<int> _pingLatencies = {};
	vector<NetworkingServerMessage> _pendingMessages = {};

	future<tuple<int, int, long long, string>> _tcpMessageThread = {};
	future<int> _connectionThread = {};

	string _username = "";
	string _serverIp = "";
	string _tcpMessageBuild = "";

	long long _lastMilliseconds = 0;

	bool _isRunning = false;
	bool _isConnectingToServer = false;
	bool _isConnectedToServer = false;
	bool _isAcceptedByServer = false;
	bool _isWaitingForPing = false;
	bool _mustDisconnectFromServer = false;

	SOCKET _tcpSocket = {};
	SOCKET _udpSocket = {};
};