#include "network_client_api.hpp"
#include "logger.hpp"

const bool NetworkClientAPI::isValidServerIP(const string& serverIP) const
{
	return (NetworkUtils::isValidIP(serverIP) && (serverIP != "0.0.0.0"));
}

const bool NetworkClientAPI::isRunning() const
{
	return _isRunning;
}

const bool NetworkClientAPI::isConnectingToServer() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::isConnectingToServer");
	}

	return _isConnectingToServer;
}

const bool NetworkClientAPI::isConnectedToServer() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::isConnectedToServer");
	}

	return _isConnectedToServer;
}

const bool NetworkClientAPI::isAcceptedByServer() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::isAcceptedByServer");
	}

	return _isAcceptedByServer;
}

const unsigned int NetworkClientAPI::getPingLatency() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::getPingLatency::1");
	}

	// Must be connected & accepted
	if(!_isConnectedToServer || !_isAcceptedByServer)
	{
		Logger::throwError("NetworkClientAPI::getPingLatency::2");
	}

	// Check if no ping latency is measured yet
	if(_pingLatencies.empty())
	{
		return 0;
	}

	// Calculate average ping
	unsigned int totalPing = 0;
	for(const auto& ping : _pingLatencies)
	{
		totalPing += ping;
	}
	int averagePing = (totalPing / static_cast<int>(_pingLatencies.size()));

	// Return
	return averagePing;
}

const string& NetworkClientAPI::getUsername() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::getUsername::1");
	}

	return _username;
}

const string& NetworkClientAPI::getServerIP() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::getServerIP::1");
	}

	// Must be connected & accepted
	if(!_isConnectedToServer || !_isAcceptedByServer)
	{
		Logger::throwError("NetworkClientAPI::getServerIP::2");
	}

	return _serverIP;
}

const vector<NetworkServerMessage>& NetworkClientAPI::getPendingMessages() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::getPendingMessages");
	}

	return _pendingMessages;
}

void NetworkClientAPI::sendMessageTCP(const string& content)
{
	_sendMessageTCP(content, false, true);
}

void NetworkClientAPI::sendMessageUDP(const string& content)
{
	_sendMessageUDP(content, false, true);
}