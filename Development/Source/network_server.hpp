#pragma once

#include <string>
#include <future>
#include <vector>

using std::string;
using std::vector;
using std::pair;

// Manually declare SOCKET, because winsock2.h cannot be included in this header
typedef unsigned __int64 SOCKET;

class NetworkServer final
{
public:
	void start();
	void stop();
	void update();

	bool isRunning();

private:
	SOCKET _waitForClientConnection(SOCKET listenSocketID);
	pair<int, string> _waitForClientMessage(SOCKET clientSocketID);

	static inline const string SERVER_PORT = "61205";

	SOCKET _listenSocketID;

	std::future<SOCKET> _connectionThread;

	vector<SOCKET> _clientSocketIDs;
	vector<string> _clientIPs;
	vector<std::future<pair<int, string>>> _clientMessageThreads;

	bool _isRunning = false;
};