#pragma once

#include "networking_client_message.hpp"
#include "networking_utils.hpp"

#include <future>
#include <vector>
#include <memory>
#include <tuple>

using std::make_shared;
using std::make_tuple;
using std::vector;
using std::future;
using std::shared_ptr;
using std::tuple;

class NetworkingServer final
{
public:
	NetworkingServer();
	~NetworkingServer();

	// VOID
	void start(unsigned int maxClientCount);
	void update();
	void sendTcpMessage(const string& username, const string& content);
	void sendUdpMessage(const string& username, const string& content);
	void broadcastTcpMessage(const string& content, const string& exceptionUsername);
	void broadcastUdpMessage(const string& content, const string& exceptionUsername);
	void disconnectClient(const string& username);
	void disconnectClients();
	void stop();

	// STRING
	const vector<string> getClientIPs() const;
	const vector<string> getClientUsernames() const;
	const string getNewClientIP() const;
	const string getNewClientUsername() const;
	const string getOldClientIP() const;
	const string getOldClientUsername() const;

	// BOOL
	const bool isRunning() const;
	const bool isClientConnected(const string& username) const;

	// MISCELLANEOUS
	const vector<NetworkingClientMessage>& getPendingMessages() const;

private:
	// VOID
	void _disconnectClient(SOCKET socket);

	// STRING
	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET socket) const;
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET socket) const;

	// BOOL
	const bool _sendTcpMessage(SOCKET socket, const string& content, bool isReserved);
	const bool _sendUdpMessage(const string& clientIP, const string& clientPort, const string& content, bool isReserved) const;

	// MISCELLANEOUS
	const SOCKET _waitForClientConnection(SOCKET socket) const;

	// STRING
	vector<future<tuple<int, int, long long, string>>> _tcpMessageThreads;
	vector<string> _tcpMessageBuilds;
	vector<string> _clientIPs;
	vector<string> _tcpClientPorts;
	vector<string> _udpClientPorts;
	vector<string> _clientUsernames;
	vector<string> _oldClientIPs;
	vector<string> _oldClientUsernames;
	string _newClientIP = "";
	string _newClientUsername = "";

	// UNSIGNED INT
	unsigned int _maxClientCount = 0;

	// BOOL
	bool _isRunning = false;

	// MISCELLANEOUS
	vector<NetworkingClientMessage> _pendingMessages;
	vector<SOCKET> _clientSockets;
	future<SOCKET> _connectionThread;
	SOCKET _tcpSocket;
	SOCKET _udpSocket;
};