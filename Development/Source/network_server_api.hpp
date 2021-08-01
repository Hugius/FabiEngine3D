#pragma once

#include "network_client_message.hpp"
#include "network_utils.hpp"

#include <future>
#include <vector>
#include <memory>
#include <tuple>

using std::make_shared;
using std::make_tuple;
using std::vector;
using std::future;
using std::shared_ptr;
using std::tuple;

class NetworkServerAPI final
{
public:
	NetworkServerAPI();
	~NetworkServerAPI();

	void start(unsigned int maxClientCount);
	void update();
	void sendTcpMessage(const string& username, const string& content);
	void sendUdpMessage(const string& username, const string& content);
	void broadcastTcpMessage(const string& content, const string& exceptionUsername);
	void broadcastUdpMessage(const string& content, const string& exceptionUsername);
	void disconnectClient(const string& username);
	void stop();

	bool isRunning();
	bool isClientConnected(const string& username);

	const string& getNewClientIP();
	const string& getNewClientPort();
	const string& getNewClientUsername();
	const string getOldClientIP();
	const string getOldClientPort();
	const string getOldClientUsername();

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
	vector<SOCKET> _clientSocketIDs;
	vector<string> _clientIPs;
	vector<string> _clientPorts;
	vector<string> _clientUsernames;
	vector<string> _clientTcpMessageBuilds;
	vector<string> _oldClientIPs;
	vector<string> _oldClientPorts;
	vector<string> _oldClientUsernames;
	unsigned int _maxClientCount;
	string _newClientIP;
	string _newClientPort;
	string _newClientUsername;

	// Message variables
	vector<NetworkClientMessage> _pendingMessages;
	vector<future<tuple<int, int, long long, string>>> _tcpMessageThreads;
	SOCKET _udpMessageSocketID;

	// Miscellaneous variables
	bool _isRunning;
};