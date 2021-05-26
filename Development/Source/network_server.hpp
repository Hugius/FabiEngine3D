#pragma once

#include "network_request.hpp"

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
	void loadNextRequest();

	bool isRunning();
	bool isRequestPending();

	const shared_ptr<NetworkRequest> getPendingRequest();

private:
	void _saveClient(SOCKET clientSocketID);
	void _deleteClient(const string& ipAddress);
	SOCKET _waitForClientConnection(SOCKET listenSocketID);
	tuple<int, string, int> _waitForClientRequest(SOCKET clientSocketID);

	static inline const string SERVER_PORT = "61205";
	static inline const unsigned int MAX_REQUEST_BYTES = 512;

	SOCKET _listenSocketID;

	future<SOCKET> _connectionThread;

	vector<SOCKET> _clientSocketIDs;
	vector<string> _clientIPs;
	vector<future<tuple<int, string, int>>> _clientRequestThreads;
	vector<shared_ptr<NetworkRequest>> _requestQueue;

	bool _isRunning = false;
};