#pragma once

#include "network_message.hpp"
#include "network_utils.hpp"

#include <future>
#include <vector>
#include <memory>
#include <tuple>

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

	void start(unsigned int customMaxClientCount);
	void stop();
	void update();
	void sendMessage(const NetworkMessage& message);
	void broadcastMessage(const string& content);

	bool isRunning();
	bool isClientConnected(const string& ipAddress, const string& port);

	const vector<NetworkMessage>& getPendingMessages();

	const vector<string> getClientIPs();
	const vector<string> getClientPorts();
	const vector<string> getClientUsernames();

private:
	void _sendMessage(SOCKET clientSocketID, const string& content, bool isReserved);
	void _acceptClient(SOCKET clientSocketID);
	void _disconnectClient(SOCKET clientSocketID);
	SOCKET _waitForClientConnection(SOCKET connectionSocketID);
	tuple<int, int, string> _waitForClientMessage(SOCKET clientSocketID);

	SOCKET _connectionSocketID;
	future<SOCKET> _connectionThread;

	vector<SOCKET> _rejectedClientSocketIDs;
	vector<SOCKET> _clientSocketIDs;
	vector<string> _clientIPs;
	vector<string> _clientPorts;
	vector<string> _clientUsernames;

	vector<NetworkMessage> _pendingMessages;
	vector<future<tuple<int, int, string>>> _messageThreads;

	string _currentMessageBuild = "";

	unsigned int _customMaxClientCount = NetworkUtils::MAX_CLIENT_COUNT;

	bool _isRunning = false;
};