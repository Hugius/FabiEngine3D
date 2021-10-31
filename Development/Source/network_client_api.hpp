#pragma once

#include "network_utils.hpp"
#include "network_server_message.hpp"

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

class NetworkClientAPI final
{
public:
	NetworkClientAPI();
	~NetworkClientAPI();

	// Voids
	void start(const string& username);
	void update();
	void connectToServer(const string& serverIP, const string& serverPort);
	void disconnectFromServer(bool mustBeAccepted = true);
	void sendTcpMessage(const string& content);
	void sendUdpMessage(const string& content);
	void stop();

	// Strings
	const string& getUsername();
	const string& getServerIP();

	// Integers
	const unsigned int getPingLatency();

	// Booleans
	const bool isValidServerIP(const string& serverIP);
	const bool isRunning();
	const bool isConnectingToServer();
	const bool isConnectedToServer();
	const bool isAcceptedByServer();

	// Miscellaneous
	const vector<NetworkServerMessage>& getPendingMessages();

private:
	// Voids
	void _setupTCP();
	void _setupUDP();

	// Strings
	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET tcpSocketID);
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET udpSocketID);

	// Integers
	int _waitForServerConnection(SOCKET serverSocketID, const string& serverIP, const string& serverPort);

	// Booleans
	bool _sendTcpMessage(const string& content, bool isReserved, bool mustBeAccepted);
	bool _sendUdpMessage(const string& content, bool isReserved, bool mustBeAccepted);

	// Strings
	future<tuple<int, int, long long, string>> _tcpMessageThread;
	string _username = "";
	string _serverIP = "";
	string _serverPort = "";
	string _tcpMessageBuild = "";

	// Integers
	vector<unsigned int> _pingLatencies;
	future<int> _connectionThread;
	long long _lastMilliseconds = 0;

	// Booleans
	bool _isRunning = false;
	bool _isConnectingToServer = false;
	bool _isConnectedToServer = false;
	bool _isAcceptedByServer = false;
	bool _isWaitingForPing = false;
	bool _mustDisconnectFromServer = false;

	// Miscellaneous
	vector<NetworkServerMessage> _pendingMessages;
	SOCKET _tcpSocketID;
	SOCKET _udpSocketID;
};