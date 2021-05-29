#pragma once

#include "network_message.hpp"
#include "network_utils.hpp"

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

	void start(const string& serverIP, const string& serverPort);
	void stop();
	void update();
	void sendMessage(const string& content);

	bool isRunning();
	bool isConnectedToServer();

	const vector<NetworkMessage>& getPendingMessages();

private:
	void _initiateConnection();
	void _closeConnection();
	int _connectWithServer(SOCKET serverSocketID, addrinfo* addressInfo);
	tuple<int, string, int> _waitForServerMessage(SOCKET serverSocketID);

	SOCKET _serverSocketID;

	future<int> _connectionThread;
	future<tuple<int, string, int>> _serverMessageThread;

	vector<NetworkMessage> _pendingMessages;

	addrinfo* _addressInfo = nullptr;

	bool _isRunning = false;
	bool _isConnectedToServer = false;
};