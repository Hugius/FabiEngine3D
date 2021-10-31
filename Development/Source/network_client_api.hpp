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
	void sendMessageTCP(const string& content);
	void sendMessageUDP(const string& content);
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
	tuple<int, int, long long, string> _waitForMessageTCP(SOCKET socket);
	tuple<int, int, string, string, string> _receiveMessageUDP(SOCKET socket);

	// Integers
	int _waitForServerConnection(SOCKET socket, const string& serverIP, const string& serverPort);

	// Booleans
	bool _sendMessageTCP(const string& content, bool isReserved, bool mustBeAccepted);
	bool _sendMessageUDP(const string& content, bool isReserved, bool mustBeAccepted);

	// Strings
	future<tuple<int, int, long long, string>> _messageThreadTCP;
	string _username = "";
	string _serverIP = "";
	string _serverPort = "";
	string _messageBuildTCP = "";

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
	SOCKET _socketTCP;
	SOCKET _socketUDP;
};