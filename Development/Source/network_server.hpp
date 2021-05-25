#pragma once

#include "network_request.hpp"

#include <string>
#include <future>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::pair;
using std::future;
using std::map;

class NetworkServer final
{
public:
	NetworkServer();
	~NetworkServer();

	void start();
	void stop();
	void update();
	void loadNextRequest();

	bool isRunning();
	bool isRequestPending();

	const NetworkRequest getPendingRequest();

private:
	void _saveClient(SOCKET clientSocketID);
	void _deleteClient(const string& ipAddress);
	SOCKET _waitForClientConnection(SOCKET listenSocketID);
	pair<int, string> _waitForClientRequest(SOCKET clientSocketID);

	static inline const string SERVER_PORT = "61205";
	static inline const unsigned int MAX_REQUEST_BYTES = 512;

	SOCKET _listenSocketID;

	future<SOCKET> _connectionThread;

	vector<SOCKET> _clientSocketIDs;
	vector<string> _clientIPs;
	vector<future<pair<int, string>>> _clientRequestThreads;
	vector<NetworkRequest> _receivedRequestQueue;

	bool _isRunning = false;
};