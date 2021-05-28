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

class NetworkServerTCP final
{
public:
	NetworkServerTCP();
	~NetworkServerTCP();

	void start();
	void stop();
	void update();
	void sendMessage(const NetworkMessage& message);
	void broadcastMessage(const string& content);

	bool isRunning();

	const vector<NetworkMessage>& getReceivedMessages();

	static inline const string SERVER_PORT = "61205";

private:
	void _sendMessage(SOCKET clientSocketID, const string& content);
	void _acceptClient(SOCKET clientSocketID);
	void _disconnectClient(SOCKET clientSocketID);
	SOCKET _waitForClientConnection(SOCKET connectionSocketID);
	tuple<int, int, string> _waitForClientMessage(SOCKET clientSocketID);

	static inline const unsigned int MAX_MESSAGE_BYTES = 512;
	static inline const unsigned int MAX_CLIENT_COUNT = 100;

	SOCKET _connectionSocketID;
	
	future<SOCKET> _connectionThread;
	
	vector<SOCKET> _clientSocketIDs;
	vector<string> _clientIPs;
	vector<string> _clientPorts;
	vector<NetworkMessage> _receivedMessages;
	vector<future<tuple<int, int, string>>> _messageThreads;

	bool _isRunning = false;
};