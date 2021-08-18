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
		Logger::throwError("NetworkClientAPI::isConnectingToServer");
	}

	return _isConnectingToServer;
}

const bool NetworkClientAPI::isConnectedToServer()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::isConnectedToServer");
	}

	return (_isConnectedToServer && _isAcceptedByServer);
}

const bool NetworkClientAPI::isAcceptedByServer()
{
	return _isAcceptedByServer;
}

const unsigned int NetworkClientAPI::getPingLatency()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::getPingLatency::1");
	}

	// Must be connected & accepted
	if (!_isConnectedToServer || !_isAcceptedByServer)
	{
		Logger::throwError("NetworkClientAPI::getPingLatency::2");
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
		Logger::throwError("NetworkClientAPI::getServerIP::1");
	}

	// Must be connected & accepted
	if (!_isConnectedToServer || !_isAcceptedByServer)
	{
		Logger::throwError("NetworkClientAPI::getServerIP::2");
	}

	return _serverIP;
}

const vector<NetworkServerMessage>& NetworkClientAPI::getPendingMessages()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::getPendingMessages");
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