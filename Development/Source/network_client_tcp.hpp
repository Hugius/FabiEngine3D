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

struct addrinfo;

class NetworkClientTCP final
{
public:
	NetworkClientTCP();
	~NetworkClientTCP();

	void start(const string& username);
	void update();
	void connectToServer(const string& serverIP, const string& serverPort);
	void disconnectFromServer();
	void sendMessage(const string& content);
	void stop();

	const bool isRunning();
	const bool isConnectingToServer();
	const bool isConnectedToServer();

	const unsigned int getServerPing();

	const string getServerIP();

	const vector<NetworkServerMessage>& getPendingMessages();

private:
	bool _sendMessage(const string& content, bool isReserved);
	int _waitForServerConnection(SOCKET serverSocketID, addrinfo* addressInfo);
	tuple<int, int, long long, string> _waitForServerMessage(SOCKET serverSocketID);

	addrinfo* _addressInfo = nullptr;

	SOCKET _serverSocketID;

	future<int> _connectionThread;
	future<tuple<int, int, long long, string>> _serverMessageThread;

	vector<NetworkServerMessage> _pendingMessages;

	string _currentMessageBuild = "";
	string _username = "";

	vector<unsigned int> _serverPings;

	long long _lastMilliseconds = 0;

	bool _isRunning = false;
	bool _isConnectingToServer = false;
	bool _isConnectedToServer = false;
	bool _isAcceptedByServer = false;
	bool _isWaitingForPing = false;
};