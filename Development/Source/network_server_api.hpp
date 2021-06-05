#pragma once

#include "network_client_message.hpp"
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

class NetworkServerAPI final
{
public:
	NetworkServerAPI();
	~NetworkServerAPI();

	void start(unsigned int customMaxClientCount);
	void update();
	void sendMessageTCP(const string& username, const string& content);
	void broadcastMessageTCP(const string& content);
	void disconnectClient(const string& username);
	void stop();

	bool isRunning();
	bool isClientConnected(const string& username);

	const vector<NetworkClientMessage>& getPendingMessages();

	const vector<string> getClientIPs();
	const vector<string> getClientPorts();
	const vector<string> getClientUsernames();

private:
	// Message functions
	void _sendMessageTCP(SOCKET clientSocketID, const string& content, bool isReserved);
	tuple<int, int, long long, string> _waitForClientMessageTCP(SOCKET clientSocketID);
	tuple<int, int, long long, string, string, string> _waitForClientMessageUDP(SOCKET udpMessageSocketID);

	// Client functions
	void _acceptClient(SOCKET clientSocketID);
	void _disconnectClient(SOCKET clientSocketID);
	SOCKET _waitForClientConnection(SOCKET connectionSocketID);

	// Connection variables
	SOCKET _connectionSocketID;
	future<SOCKET> _connectionThread;

	// Client variables
	vector<SOCKET> _disconnectingClientSocketIDs;
	vector<SOCKET> _clientSocketIDs;
	vector<string> _clientIPs;
	vector<string> _clientPorts;
	vector<string> _clientUsernames;
	unsigned int _customMaxClientCount = NetworkUtils::MAX_CLIENT_COUNT;

	// Message variables
	vector<NetworkClientMessage> _pendingMessages;
	vector<future<tuple<int, int, long long, string>>> _tcpMessageThreads;
	future<tuple<int, int, long long, string, string, string>> _udpMessageThread;
	string _currentTcpMessageBuild = "";

	// Miscellaneous variables
	SOCKET _udpSocketID;
	bool _isRunning = false;
};