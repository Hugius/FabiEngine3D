#pragma once

#include "network_utils.hpp"
#include "network_server_message.hpp"

#include <string>
#include <future>
#include <vector>
#include <memory>
#include <tuple>

using std::string;
using std::vector;
using std::future;
using std::shared_ptr;
using std::tuple;
using std::make_shared;
using std::make_tuple;

class NetworkClientAPI final
{
public:
	NetworkClientAPI();
	~NetworkClientAPI();

	void start(const string& username);
	void update();
	void connectToServer(const string& serverIP, const string& serverPort);
	void disconnectFromServer();
	void sendTcpMessage(const string& content);
	void sendUdpMessage(const string& content);
	void stop();

	const bool isRunning();
	const bool isConnectingToServer();
	const bool isConnectedToServer();

	const unsigned int getPingLatency();

	const string getServerIP();

	const vector<NetworkServerMessage>& getPendingMessages();

private:
	// Message functions
	bool _sendTcpMessage(const string& content, bool isReserved);
	bool _sendUdpMessage(const string& content);
	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET tcpSocketID);
	tuple<int, int, long long, string, string, string> _receiveUdpMessage(SOCKET udpSocketID);

	// Miscellaneous functions
	int _waitForServerConnection(SOCKET serverSocketID, const string& serverIP, const string& serverPort);
	void _setupTCP();
	void _setupUDP(const string& tcpPort);

	// Connection variables
	SOCKET _connectionSocketID;
	future<int> _connectionThread;

	// Message variables
	future<tuple<int, int, long long, string>> _tcpMessageThread;
	vector<NetworkServerMessage> _pendingMessages;
	string _currentTcpMessageBuild = "";
	SOCKET _udpMessageSocketID;

	// Ping variables
	vector<unsigned int> _pingLatencies;
	long long _lastMilliseconds = 0;

	// State variables
	bool _isRunning = false;
	bool _isConnectingToServer = false;
	bool _isConnectedToServer = false;
	bool _isAcceptedByServer = false;
	bool _isWaitingForPing = false;

	// Miscellaneous variables
	string _username = "";
	string _serverIP = "";
	string _serverPort = "";
};