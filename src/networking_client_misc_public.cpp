#include "networking_client.hpp"
#include "logger.hpp"
#include "mathematics.hpp"

const bool NetworkingClient::isValidServerIP(const string& serverIP) const
{
	return (isValidIP(serverIP) && (serverIP != "0.0.0.0"));
}

const bool NetworkingClient::isRunning() const
{
	return _isRunning;
}

const bool NetworkingClient::isConnectingToServer() const
{
	if(!_isRunning)
	{
		abort();
	}

	return _isConnectingToServer;
}

const bool NetworkingClient::isConnectedToServer() const
{
	if(!_isRunning)
	{
		abort();
	}

	return _isConnectedToServer;
}

const bool NetworkingClient::isAcceptedByServer() const
{
	if(!_isRunning)
	{
		abort();
	}

	return _isAcceptedByServer;
}

const unsigned int NetworkingClient::getPingLatency() const
{
	if(!_isRunning)
	{
		abort();
	}

	if(!_isConnectedToServer || !_isAcceptedByServer)
	{
		abort();
	}

	if(_pingLatencies.empty())
	{
		return 0;
	}

	return Math::calculateAverage(_pingLatencies);
}

const string& NetworkingClient::getUsername() const
{
	if(!_isRunning)
	{
		abort();
	}

	return _username;
}

const string& NetworkingClient::getServerIP() const
{
	if(!_isRunning)
	{
		abort();
	}

	if(!_isConnectedToServer || !_isAcceptedByServer)
	{
		abort();
	}

	return _serverIP;
}

const vector<NetworkingServerMessage>& NetworkingClient::getPendingMessages() const
{
	if(!_isRunning)
	{
		abort();
	}

	return _pendingMessages;
}

void NetworkingClient::sendTcpMessage(const string& content)
{
	_sendTcpMessage(content, false, true);
}

void NetworkingClient::sendUdpMessage(const string& content)
{
	_sendUdpMessage(content, false, true);
}