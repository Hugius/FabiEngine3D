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

class NetworkServerTCP final
{
public:
	NetworkServerTCP();
	~NetworkServerTCP();

	void start();
	void stop();
	void update();
	void sendMessage(const NetworkMessage& message);
	void broadcastMessage(const string& content);

	bool isRunning();

	const vector<NetworkMessage>& getPendingMessages();

private:
	void _sendMessage(SOCKET clientSocketID, const string& content);
	void _acceptClient(SOCKET clientSocketID);
	void _disconnectClient(SOCKET clientSocketID);
	SOCKET _waitForClientConnection(SOCKET connectionSocketID);
	tuple<int, int, string> _waitForClientMessage(SOCKET clientSocketID);

	SOCKET _connectionSocketID;
	future<SOCKET> _connectionThread;
	
	vector<SOCKET> _clientSocketIDs;
	vector<string> _clientIPs;
	vector<string> _clientPorts;

	vector<NetworkMessage> _pendingMessages;
	vector<future<tuple<int, int, string>>> _messageThreads;

	bool _isRunning = false;
};