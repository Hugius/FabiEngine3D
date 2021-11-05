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
	void sendMessageTCP(const string& username, const string& content);
	void sendMessageUDP(const string& username, const string& content);
	void broadcastMessageTCP(const string& content, const string& exceptionUsername);
	void broadcastMessageUDP(const string& content, const string& exceptionUsername);
	void disconnectClient(const string& username);
	void disconnectClients();
	void stop();

	// Strings
	const vector<string> getClientIPs();
	const vector<string> getClientUsernames();
	const string& getNewClientIP();
	const string& getNewClientUsername();
	const string getOldClientIP();
	const string getOldClientUsername();

	// Booleans
	bool isRunning();
	bool isClientConnected(const string& username);

	// Miscellaneous
	const vector<NetworkClientMessage>& getPendingMessages();

private:
	// Voids
	void _disconnectClient(SOCKET socket);

	// Strings
	tuple<int, int, long long, string> _waitForMessageTCP(SOCKET socket);
	tuple<int, int, string, string, string> _receiveMessageUDP(SOCKET socket);

	// Booleans
	bool _sendMessageTCP(SOCKET socket, const string& content, bool isReserved);
	bool _sendMessageUDP(const string& clientIP, const string& clientPort, const string& content, bool isReserved);

	// Miscellaneous
	SOCKET _waitForClientConnection(SOCKET socket);

	// Strings
	vector<future<tuple<int, int, long long, string>>> _messageThreadsTCP;
	vector<string> _messageBuildsTCP;
	vector<string> _clientIPs;
	vector<string> _clientPortsTCP;
	vector<string> _clientPortsUDP;
	vector<string> _clientUsernames;
	vector<string> _oldClientIPs;
	vector<string> _oldClientUsernames;
	string _newClientIP = "";
	string _newClientUsername = "";

	// Integers
	unsigned int _maxClientCount = 0;

	// Booleans
	bool _isRunning = false;

	// Miscellaneous
	vector<NetworkClientMessage> _pendingMessages;
	vector<SOCKET> _clientSockets;
	future<SOCKET> _connectionThread;
	SOCKET _socketTCP;
	SOCKET _socketUDP;
};