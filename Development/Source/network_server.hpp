#pragma once

#include <string>

using std::string;

// Manually declare SOCKET, because winsock2.h cannot be included in this header
typedef unsigned __int64 SOCKET;

class NetworkServer final
{
public:
	void start();
	void stop();
	void update();

private:
	static inline const string SERVER_PORT = "61205";

	SOCKET _listenSocket;
	SOCKET _clientSocket;

	bool _isRunning = false;
};