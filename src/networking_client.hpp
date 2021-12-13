#pragma once

#include "networking_utils.hpp"
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

class NetworkingClient final
{
public:
	NetworkingClient();
	~NetworkingClient();

	// VOID
	void start(const string& username);
	void update();
	void connectToServer(const string& serverIP, const string& serverPort);
	void disconnectFromServer(bool mustBeAccepted);
	void sendTcpMessage(const string& content);
	void sendUdpMessage(const string& content);
	void stop();

	// STRING
	const string& getUsername() const;
	const string& getServerIP() const;

	// UNSIGNED INT
	const unsigned int getPingLatency() const;

	// BOOL
	const bool isValidServerIP(const string& serverIP) const;
	const bool isRunning() const;
	const bool isConnectingToServer() const;
	const bool isConnectedToServer() const;
	const bool isAcceptedByServer() const;

	// MISCELLANEOUS
	const vector<NetworkingServerMessage>& getPendingMessages() const;

private:
	// VOID
	void _setupTcp();
	void _setupUdp();

	// STRING
	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET socket) const;
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET socket) const;

	// INT
	int _waitForServerConnection(SOCKET socket, const string& serverIP, const string& serverPort) const;

	// BOOL
	bool _sendTcpMessage(const string& content, bool isReserved, bool mustBeAccepted);
	bool _sendUdpMessage(const string& content, bool isReserved, bool mustBeAccepted) const;

	// STRING
	future<tuple<int, int, long long, string>> _tcpMessageThread;
	string _username = "";
	string _serverIP = "";
	string _serverPort = "";
	string _tcpMessageBuild = "";

	// LONG LONG
	long long _lastMilliseconds = 0;

	// INT
	future<int> _connectionThread;

	// UNSIGNED INT
	vector<unsigned int> _pingLatencies;

	// BOOL
	bool _isRunning = false;
	bool _isConnectingToServer = false;
	bool _isConnectedToServer = false;
	bool _isAcceptedByServer = false;
	bool _isWaitingForPing = false;
	bool _mustDisconnectFromServer = false;

	// MISCELLANEOUS
	vector<NetworkingServerMessage> _pendingMessages;
	SOCKET _tcpSocket;
	SOCKET _udpSocket;
};