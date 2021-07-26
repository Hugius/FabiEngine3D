#include "network_client_api.hpp"
#include "logger.hpp"

const bool NetworkClientAPI::isValidServerIP(const string& serverIP)
{
	return (NetworkUtils::isValidIP(serverIP) && (serverIP != "0.0.0.0"));
}

const bool NetworkClientAPI::isRunning()
{
	return _isRunning;
}

const bool NetworkClientAPI::isConnectingToServer()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve connecting status: not running!");
	}

	return _isConnectingToServer;
}

const bool NetworkClientAPI::isConnectedToServer()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve connection status: not running!");
	}

	return (_isConnectedToServer && _isAcceptedByServer);
}

const unsigned int NetworkClientAPI::getPingLatency()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve ping latency: not running!");
	}

	// Must be connected & accepted
	if (!_isConnectedToServer || !_isAcceptedByServer)
	{
		Logger::throwWarning("Networking client tried to retrieve ping latency: not connected!");
	}

	// Calculate average ping
	unsigned int totalPing = 0;
	for (const auto& ping : _pingLatencies)
	{
		totalPing += ping;
	}
	return (totalPing / static_cast<int>(_pingLatencies.size()));
}

const string& NetworkClientAPI::getUsername()
{
	return _username;
}

const string& NetworkClientAPI::getServerIP()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not running!");
	}

	// Must be connected & accepted
	if (!_isConnectedToServer || !_isAcceptedByServer)
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not connected!");
	}

	return _serverIP;
}

const vector<NetworkServerMessage>& NetworkClientAPI::getPendingMessages()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve pending messages: not running!");
	}

	return _pendingMessages;
}

void NetworkClientAPI::sendTcpMessage(const string& content)
{
	_sendTcpMessage(content, false, true);
}

void NetworkClientAPI::sendUdpMessage(const string& content)
{
	_sendUdpMessage(content, false, true);
}