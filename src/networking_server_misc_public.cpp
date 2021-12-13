#include "networking_server.hpp"
#include "logger.hpp"

const bool NetworkingServer::isRunning() const
{
	return _isRunning;
}

const bool NetworkingServer::isClientConnected(const string& username) const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::isClientConnected");
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

const string NetworkingServer::getNewClientIP() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getNewClientIP");
	}

	// Return
	return _newClientIP;
}

const string NetworkingServer::getNewClientUsername() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getNewClientUsername");
	}

	// Return
	return _newClientUsername;
}

const string NetworkingServer::getOldClientIP() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getOldClientIP");
	}

	// Return
	if(_oldClientIPs.empty())
	{
		return "";
	}
	else
	{
		return _oldClientIPs[0];
	}
}

const string NetworkingServer::getOldClientUsername() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getOldClientUsername");
	}

	// Return
	if(_oldClientUsernames.empty())
	{
		return "";
	}
	else
	{
		return _oldClientUsernames[0];
	}
}

const vector<NetworkingClientMessage>& NetworkingServer::getPendingMessages() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getPendingMessages");
	}

	// Return
	return _pendingMessages;
}

const vector<string> NetworkingServer::getClientIPs() const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getClientIPs");
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

const vector<string> NetworkingServer::getClientUsernames() const
{
	// Temporary values
	vector<string> clientUsernames;

	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getClientUsernames");
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

void NetworkingServer::sendTcpMessage(const string& username, const string& content)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::sendTcpMessage::1");
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
				_sendTcpMessage(_clientSockets[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwError("NetworkingServer::sendTcpMessage::2");
}

void NetworkingServer::sendUdpMessage(const string& username, const string& content)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::sendUdpMessage::1");
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
				_sendUdpMessage(_clientIPs[i], _udpClientPorts[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwError("NetworkingServer::sendUdpMessage::2");
}

void NetworkingServer::broadcastTcpMessage(const string& content, const string& exceptionUsername)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::broadcastTcpMessage");
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
				_sendTcpMessage(_clientSockets[i], content, false);
			}
		}
	}
}

void NetworkingServer::broadcastUdpMessage(const string& content, const string& exceptionUsername)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::broadcastUdpMessage");
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
				_sendUdpMessage(_clientIPs[i], _udpClientPorts[i], content, false);
			}
		}
	}
}

void NetworkingServer::disconnectClient(const string& username)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::disconnectClient::1");
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
				_sendTcpMessage(_clientSockets[i], "DISCONNECTED", true);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwError("NetworkingServer::disconnectClient::2");
}

void NetworkingServer::disconnectClients()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::disconnectClients::1");
	}

	// Send messages
	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if(!_clientUsernames[i].empty())
		{
			_sendTcpMessage(_clientSockets[i], "DISCONNECTED", true);
			return;
		}
	}
}