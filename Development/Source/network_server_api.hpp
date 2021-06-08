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
	void sendTcpMessage(const string& username, const string& content);
	void sendUdpMessage(const string& username, const string& content);
	void broadcastTcpMessage(const string& content);
	void broadcastUdpMessage(const string& content);
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
	bool _sendTcpMessage(SOCKET clientSocketID, const string& content, bool isReserved);
	bool _sendUdpMessage(const string& clientIP, const string& clientPort, const string& content, bool isReserved);
	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET clientSocketID);
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET udpMessageSocketID);

	// Client functions
	bool _isClientConnected(const string& IP, const string& port);
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
	vector<string> _clientTcpMessageBuilds;
	unsigned int _customMaxClientCount = NetworkUtils::MAX_CLIENT_COUNT;

	// Message variables
	vector<NetworkClientMessage> _pendingMessages;
	vector<future<tuple<int, int, long long, string>>> _tcpMessageThreads;
	SOCKET _udpMessageSocketID;

	// Miscellaneous variables
	bool _isRunning = false;
};