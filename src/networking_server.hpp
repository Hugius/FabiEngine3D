#pragma once

#include "networking_client_message.hpp"
#include "networking_helper.hpp"

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
	void construct();
	void destruct();
	void start(int maxClientCount);
	void update();
	void sendTcpMessageToClient(const string & username, const string & content);
	void sendUdpMessageToClient(const string & username, const string & content);
	void broadcastTcpMessageToClients(const string & content);
	void broadcastUdpMessageToClients(const string & content);
	void disconnectClient(const string & username);
	void disconnectClients();
	void stop();

	const vector<string> getClientIps() const;
	const vector<string> getClientUsernames() const;
	const vector<NetworkingClientMessage> & getPendingMessages() const;

	const string getNewClientIp() const;
	const string getNewClientUsername() const;
	const string getOldClientIp() const;
	const string getOldClientUsername() const;

	const bool isRunning() const;
	const bool isClientConnected(const string & username) const;

private:
	void _disconnectClient(SOCKET socket);

	tuple<int, int, long long, string> _waitForTcpMessage(SOCKET socket) const;
	tuple<int, int, string, string, string> _receiveUdpMessage(SOCKET socket) const;

	const bool _setupTcp();
	const bool _setupUdp();
	const bool _sendTcpMessageToClient(SOCKET socket, const string & content, bool isReserved);
	const bool _sendUdpMessageToClient(const string & clientIp, const string & clientPort, const string & content, bool isReserved) const;

	const SOCKET _waitForClientConnection(SOCKET socket) const;

	vector<future<tuple<int, int, long long, string>>> _tcpMessageThreads = {};
	vector<string> _tcpMessageBuilds = {};
	vector<string> _clientIps = {};
	vector<string> _tcpClientPorts = {};
	vector<string> _udpClientPorts = {};
	vector<string> _clientUsernames = {};
	vector<string> _oldClientIps = {};
	vector<string> _oldClientUsernames = {};
	vector<NetworkingClientMessage> _pendingMessages = {};
	vector<SOCKET> _clientSockets = {};

	future<SOCKET> _connectionThread;

	string _newClientIp = "";
	string _newClientUsername = "";

	int _maxClientCount = 0;

	bool _isRunning = false;

	SOCKET _tcpSocket;
	SOCKET _udpSocket;
};