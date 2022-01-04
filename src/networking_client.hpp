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

	void start(const string& username);
	void update();
	void connectToServer(const string& serverIP, const string& serverPort);
	void disconnectFromServer(bool mustBeAccepted);
	void sendTcpMessage(const string& content);
	void sendUdpMessage(const string& content);
	void stop();

	const string& getUsername() const;
	const string& getServerIP() const;

	const unsigned int getPingLatency() const;

	const bool isValidServerIP(const string& serverIP) const;
	const bool isRunning() const;
	const bool isConnectingToServer() const;
	const bool isConnectedToServer() const;
	const bool isAcceptedByServer() const;

	const vector<NetworkingServerMessage>& getPendingMessages() const;

private:
	void _setupTcp();
	void _setupUdp();

	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET socket) const;
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET socket) const;

	int _waitForServerConnection(SOCKET socket, const string& serverIP, const string& serverPort) const;

	bool _sendTcpMessage(const string& content, bool isReserved, bool mustBeAccepted);
	bool _sendUdpMessage(const string& content, bool isReserved, bool mustBeAccepted) const;

	future<tuple<int, int, long long, string>> _tcpMessageThread;
	string _username = "";
	string _serverIP = "";
	string _serverPort = "";
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