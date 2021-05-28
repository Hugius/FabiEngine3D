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
	void sendMessage(const string& content);

	bool isRunning();
	bool isMessagePending();
	bool isConnected();

	const shared_ptr<NetworkMessage> getPendingMessage();

private:
	void _initiateConnection();
	void _closeConnection();
	void _spawnConnectionThread();
	int _connectWithServer(SOCKET serverSocketID, addrinfo* addressInfo);
	tuple<int, string, int> _waitForServerMessage(SOCKET serverSocketID);

	static inline const unsigned int MAX_MESSAGE_BYTES = 512;

	SOCKET _serverSocketID;

	future<int> _connectionThread;
	future<tuple<int, string, int>> _serverMessageThread;

	shared_ptr<NetworkMessage> _receivedMessage = nullptr;

	addrinfo* _addressInfo = nullptr;

	bool _isRunning = false;
	bool _isConnectedToServer = false;
};