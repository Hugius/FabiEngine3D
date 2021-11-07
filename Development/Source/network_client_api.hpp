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
	void disconnectFromServer(bool mustBeAccepted);
	void sendMessageTCP(const string& content);
	void sendMessageUDP(const string& content);
	void stop();

	// Strings
	const string& getUsername() const;
	const string& getServerIP() const;

	// Integers
	const unsigned int getPingLatency() const;

	// Booleans
	const bool isValidServerIP(const string& serverIP) const;
	const bool isRunning() const;
	const bool isConnectingToServer() const;
	const bool isConnectedToServer() const;
	const bool isAcceptedByServer() const;

	// Miscellaneous
	const vector<NetworkServerMessage>& getPendingMessages() const;

private:
	// Voids
	void _setupTCP();
	void _setupUDP();

	// Strings
	tuple<int, int, long long, string> _waitForMessageTCP(SOCKET socket) const;
	tuple<int, int, string, string, string> _receiveMessageUDP(SOCKET socket) const;

	// Integers
	int _waitForServerConnection(SOCKET socket, const string& serverIP, const string& serverPort) const;

	// Booleans
	bool _sendMessageTCP(const string& content, bool isReserved, bool mustBeAccepted);
	bool _sendMessageUDP(const string& content, bool isReserved, bool mustBeAccepted) const;

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