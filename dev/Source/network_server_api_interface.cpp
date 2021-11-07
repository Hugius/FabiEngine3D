#include "network_server_api.hpp"
#include "logger.hpp"

const bool NetworkServerAPI::isRunning() const
{
	return _isRunning;
}

const bool NetworkServerAPI::isClientConnected(const string& username) const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::isClientConnected");
	}

	// Try to find client
	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if(!_clientUsernames[i].empty())
		{
			// Check if client is found
			if(username == _clientUsernames[i])
			{
				return true;
			}
		}
	}

	// Return
	return false;
}

const string& NetworkServerAPI::getNewClientIP() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getNewClientIP");
	}

	// Return
	return _newClientIP;
}

const string& NetworkServerAPI::getNewClientUsername() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getNewClientUsername");
	}

	// Return
	return _newClientUsername;
}

const string NetworkServerAPI::getOldClientIP() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getOldClientIP");
	}

	// Return
	if(_oldClientIPs.empty())
	{
		return "";
	}
	else
	{
		return _oldClientIPs.front();
	}
}

const string NetworkServerAPI::getOldClientUsername() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getOldClientUsername");
	}

	// Return
	if(_oldClientUsernames.empty())
	{
		return "";
	}
	else
	{
		return _oldClientUsernames.front();
	}
}

const vector<NetworkClientMessage>& NetworkServerAPI::getPendingMessages() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getPendingMessages");
	}

	// Return
	return _pendingMessages;
}

const vector<string> NetworkServerAPI::getClientIPs() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getClientIPs");
	}

	// Client must be fully accepted
	vector<string> clientIPs;
	for(size_t i = 0; i < _clientIPs.size(); i++)
	{
		// Check if client is found
		if(!_clientUsernames[i].empty())
		{
			clientIPs.push_back(_clientIPs[i]);
		}
	}

	// Return
	return clientIPs;
}

const vector<string> NetworkServerAPI::getClientUsernames() const
{
	// Temporary values
	vector<string> clientUsernames;

	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getClientUsernames");
	}

	// Client must be fully accepted
	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			clientUsernames.push_back(_clientUsernames[i]);
		}
	}

	// Return
	return clientUsernames;
}

void NetworkServerAPI::sendMessageTCP(const string& username, const string& content)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::sendTcpMessage::1");
	}

	// Try to find client and send message
	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if(!_clientUsernames[i].empty())
		{
			// Check if client is found
			if(username == _clientUsernames[i])
			{
				_sendMessageTCP(_clientSockets[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwError("NetworkServerAPI::sendTcpMessage::2");
}

void NetworkServerAPI::sendMessageUDP(const string& username, const string& content)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::sendUdpMessage::1");
	}

	// Try to find client and send message
	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if(!_clientUsernames[i].empty())
		{
			// Check if client is found
			if(username == _clientUsernames[i])
			{
				_sendMessageUDP(_clientIPs[i], _clientPortsUDP[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwError("NetworkServerAPI::sendUdpMessage::2");
}

void NetworkServerAPI::broadcastMessageTCP(const string& content, const string& exceptionUsername)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::broadcastTcpMessage");
	}

	// Send message to all connected clients
	for(size_t i = 0; i < _clientSockets.size(); i++)
	{
		// Check exception
		if(_clientUsernames[i] != exceptionUsername)
		{
			// Client must be fully accepted
			if(!_clientUsernames[i].empty())
			{
				_sendMessageTCP(_clientSockets[i], content, false);
			}
		}
	}
}

void NetworkServerAPI::broadcastMessageUDP(const string& content, const string& exceptionUsername)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::broadcastUdpMessage");
	}

	// Try to find client and send message
	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Check exception
		if(_clientUsernames[i] != exceptionUsername)
		{
			// Client must be fully accepted
			if(!_clientUsernames[i].empty())
			{
				_sendMessageUDP(_clientIPs[i], _clientPortsUDP[i], content, false);
			}
		}
	}
}

void NetworkServerAPI::disconnectClient(const string& username)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::disconnectClient::1");
	}

	// Try to find client and send message
	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if(!_clientUsernames[i].empty())
		{
			// Check if client is found
			if(username == _clientUsernames[i])
			{
				_sendMessageTCP(_clientSockets[i], "DISCONNECTED", true);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwError("NetworkServerAPI::disconnectClient::2");
}

void NetworkServerAPI::disconnectClients()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::disconnectClients::1");
	}

	// Send messages
	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if(!_clientUsernames[i].empty())
		{
			_sendMessageTCP(_clientSockets[i], "DISCONNECTED", true);
			return;
		}
	}
}