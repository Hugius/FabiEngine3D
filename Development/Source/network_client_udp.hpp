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

struct addrinfo;

class NetworkClientUDP final
{
public:
	NetworkClientUDP();
	~NetworkClientUDP();

	void start(const string& username);
	void update();
	void sendMessage(const string& content);
	void stop();

	const bool isRunning();

	const vector<NetworkServerMessage>& getPendingMessages();

private:
	bool _sendMessage(const string& content, bool isReserved);
	tuple<int, int, long long, string> _waitForServerMessage(SOCKET serverSocketID);

	SOCKET _serverSocketID;

	future<tuple<int, int, long long, string>> _serverMessageThread;

	vector<NetworkServerMessage> _pendingMessages;

	string _username = "";

	bool _isRunning = false;
};