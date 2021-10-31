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

	// Voids
	void start(unsigned int maxClientCount);
	void update();
	void sendTcpMessage(const string& username, const string& content);
	void sendUdpMessage(const string& username, const string& content);
	void broadcastTcpMessage(const string& content, const string& exceptionUsername);
	void broadcastUdpMessage(const string& content, const string& exceptionUsername);
	void disconnectClient(const string& username);
	void stop();

	// Strings
	const vector<string> getClientIPs();
	const vector<string> getClientPorts();
	const vector<string> getClientUsernames();
	const string& getNewClientIP();
	const string& getNewClientPort();
	const string& getNewClientUsername();
	const string getOldClientIP();
	const string getOldClientPort();
	const string getOldClientUsername();

	// Booleans
	bool isRunning();
	bool isClientConnected(const string& username);

	// Miscellaneous
	const vector<NetworkClientMessage>& getPendingMessages();

private:
	// Voids
	void _disconnectClient(SOCKET clientSocketID);

	// Strings
	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET clientSocketID);
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET udpMessageSocketID);

	// booleans
	bool _isClientConnected(const string& IP, const string& port);
	bool _sendTcpMessage(SOCKET clientSocketID, const string& content, bool isReserved);
	bool _sendUdpMessage(const string& clientIP, const string& clientPort, const string& content, bool isReserved);

	// Miscellaneous
	SOCKET _waitForClientConnection(SOCKET connectionSocketID);

	// Strings
	vector<future<tuple<int, int, long long, string>>> _tcpMessageThreads;
	vector<string> _clientIPs;
	vector<string> _clientPorts;
	vector<string> _clientUsernames;
	vector<string> _clientTcpMessageBuilds;
	vector<string> _oldClientIPs;
	vector<string> _oldClientPorts;
	vector<string> _oldClientUsernames;
	string _newClientIP = "";
	string _newClientPort = "";
	string _newClientUsername = "";

	// Integers
	unsigned int _maxClientCount = 0;

	// Booleans
	bool _isRunning = false;

	// Miscellaneous
	vector<NetworkClientMessage> _pendingMessages;
	vector<SOCKET> _clientSocketIDs;
	future<SOCKET> _connectionThread;
	SOCKET _tcpSocketID;
	SOCKET _udpSocketID;
};