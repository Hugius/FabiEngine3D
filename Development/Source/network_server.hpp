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

class NetworkServer final
{
public:
	NetworkServer();
	~NetworkServer();

	void start();
	void stop();
	void update();
	void loadNextPendingMessage();
	void sendMessage(const string& ipAddress, const string& port, const string& content);
	void broadcastMessage(const string& content);

	bool isRunning();
	bool isMessagePending();

	const shared_ptr<NetworkMessage> getPendingMessage();

	static inline const string networkServer_PORT = "61205";

private:
	void _sendMessage(SOCKET clientSocketID, const string& content);
	void _acceptClient(SOCKET clientSocketID);
	void _disconnectClient(SOCKET clientSocketID);
	SOCKET _waitForClientConnection(SOCKET listenSocketID);
	tuple<int, string, int> _waitForClientMessage(SOCKET clientSocketID);

	static inline const unsigned int MAX_MESSAGE_BYTES = 512;
	static inline const unsigned int MAX_CLIENT_COUNT = 2;

	// Sockets
	SOCKET _listeningSocketID;
	vector<SOCKET> _clientSocketIDs;

	// Threads
	future<SOCKET> _connectionThread;
	vector<future<tuple<int, string, int>>> _messageThreads;
	
	vector<string> _clientIPs;
	vector<string> _clientPorts;
	vector<shared_ptr<NetworkMessage>> _receivedMessageQueue;

	bool _isRunning = false;
};