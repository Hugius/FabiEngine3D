#include "networking_client.hpp"
#include "logger.hpp"
#include "mathematics.hpp"

const bool NetworkingClient::isValidServerIP(const string& serverIP) const
{
	return (_isValidIP(serverIP) && (serverIP != "0.0.0.0"));
}

const bool NetworkingClient::isRunning() const
{
	return _isRunning;
}

const bool NetworkingClient::isConnectingToServer() const
{
	return _isConnectingToServer;
}

const bool NetworkingClient::isConnectedToServer() const
{
	return _isConnectedToServer;
}

const bool NetworkingClient::isAcceptedByServer() const
{
	return _isAcceptedByServer;
}

const unsigned int NetworkingClient::getPingLatency() const
{
	if(_pingLatencies.empty())
	{
		return 0;
	}

	return Math::calculateAverage(_pingLatencies);
}

const string& NetworkingClient::getUsername() const
{
	return _username;
}

const string& NetworkingClient::getServerIP() const
{
	return _serverIP;
}

const vector<NetworkingServerMessage>& NetworkingClient::getPendingMessages() const
{
	return _pendingMessages;
}

void NetworkingClient::sendTcpMessage(const string& content)
{
	if(!_isRunning)
	{
		abort();
	}
	if(!_isConnectedToServer || !_isAcceptedByServer)
	{
		abort();
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}
	if(isMessageReserved(content))
	{
		abort();
	}
	if(content.size() > MAX_MESSAGE_SIZE)
	{
		abort();
	}

	_sendTcpMessage(content, false, true);
}

void NetworkingClient::sendUdpMessage(const string& content)
{
	if(!_isRunning)
	{
		abort();
	}
	if(!_isConnectedToServer || !_isAcceptedByServer)
	{
		abort();
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}
	if(isMessageReserved(content))
	{
		abort();
	}
	if(content.size() > MAX_MESSAGE_SIZE)
	{
		abort();
	}

	_sendUdpMessage(content, false, true);
}

const unsigned int NetworkingClient::getMaxUsernameSize() const
{
	return MAX_USERNAME_SIZE;
}

const unsigned int NetworkingClient::getMaxMessageSize()
{
	return MAX_MESSAGE_SIZE;
}