#pragma once

#include <string>
#include <future>
#include <vector>

using std::string;
using std::vector;

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
	SOCKET _waitForClient(SOCKET listenSocketID);

	static inline const string SERVER_PORT = "61205";

	SOCKET _listenSocketID;
	vector<SOCKET> _clientSocketIDs;

	std::future<SOCKET>* _listeningThread = nullptr;

	bool _isRunning = false;
};