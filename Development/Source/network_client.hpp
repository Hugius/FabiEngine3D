#pragma once

#include "network_message.hpp"

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

class NetworkClient final
{
public:
	NetworkClient();
	~NetworkClient();

	void start(const string& serverIP, const string& serverPort);
	void stop();
	void update();
	void loadNextMessage();

	bool isRunning();
	bool isMessagePending();

	const shared_ptr<NetworkMessage> getPendingMessage();

private:
	void _sendMessageToServer(const string& content);
	int _connectWithServer(SOCKET serverSocketID, addrinfo* addressInfo);
	tuple<int, string, int> _waitForServerMessage(SOCKET clientSocketID);

	static inline const unsigned int MAX_MESSAGE_BYTES = 512;
	static inline const unsigned int MAX_CLIENT_COUNT = 1;

	SOCKET _serverSocketID;

	future<int> _connectionThread;

	future<tuple<int, string, int>> _serverMessageThread;
	vector<shared_ptr<NetworkMessage>> _receivedMessageQueue;

	addrinfo* _addressInfo = nullptr;

	bool _isRunning = false;
};