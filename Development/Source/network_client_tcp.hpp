#pragma once

#include "network_message.hpp"
#include "network_utils.hpp"

#include <string>
#include <future>
#include <vector>
#include <memory>
#include <tuple>
#include <chrono>

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

	void start(const string& serverIP, const string& serverPort, const string& username);
	void stop();
	void update();
	void sendMessage(const string& content);

	const bool isRunning();
	const bool isConnectedToServer();

	const unsigned int getPingMS();

	const vector<NetworkMessage>& getPendingMessages();

private:
	void _initiateConnection();
	void _closeConnection();
	void _sendMessage(const string& content, bool isReserved);
	int _connectWithServer(SOCKET serverSocketID, addrinfo* addressInfo);
	tuple<int, string, int> _waitForServerMessage(SOCKET serverSocketID);
	unsigned int _getCurrentTimeMS();

	SOCKET _serverSocketID;

	future<int> _connectionThread;
	future<tuple<int, string, int>> _serverMessageThread;

	vector<NetworkMessage> _pendingMessages;

	addrinfo* _addressInfo = nullptr;

	string _currentMessageBuild = "";
	string _username = "";

	unsigned int _pingMS = 0;
	unsigned int _lastTimeMS = 0;

	bool _isRunning = false;
	bool _isConnectedToServer = false;
	bool _isAcceptedByServer = false;
	bool _isWaitingForPing = false;
};