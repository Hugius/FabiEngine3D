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

class NetworkClientAPI final
{
public:
	NetworkClientAPI();
	~NetworkClientAPI();

	void start(const string& username);
	void update();
	void connectToServer(const string& serverIP, const string& serverPort);
	void disconnectFromServer();
	void sendMessageTCP(const string& content);
	void sendMessageUDP(const string& content);
	void stop();

	const bool isRunning();
	const bool isConnectingToServer();
	const bool isConnectedToServer();

	const unsigned int getPingLatency();

	const string getServerIP();

	const vector<NetworkServerMessage>& getPendingMessages();

private:
	int _waitForServerConnection(SOCKET serverSocketID, const string& serverIP, const string& serverPort);
	bool _sendMessageTCP(const string& content, bool isReserved);
	bool _sendMessageUDP(const string& content);
	tuple<int, int, long long, string> _waitForServerMessageTCP(SOCKET tcpServerSocketID);
	tuple<int, int, long long, string> _waitForServerMessageUDP(SOCKET udpServerSocketID);

	SOCKET _tcpServerSocketID;
	SOCKET _udpServerSocketID;

	future<int> _connectionThread;
	future<tuple<int, int, long long, string>> _serverMessageThreadTCP;
	future<tuple<int, int, long long, string>> _serverMessageThreadUDP;

	vector<NetworkServerMessage> _pendingMessages;

	string _currentTcpMessageBuild = "";
	string _username = "";
	string _serverIP = "";
	string _serverPort = "";

	vector<unsigned int> _pingLatencies;

	long long _lastMilliseconds = 0;

	bool _isRunning = false;
	bool _isConnectingToServer = false;
	bool _isConnectedToServer = false;
	bool _isAcceptedByServer = false;
	bool _isWaitingForPing = false;
};