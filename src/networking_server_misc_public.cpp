#include "networking_server.hpp"
#include "logger.hpp"

const bool NetworkingServer::isRunning() const
{
	return _isRunning;
}

const bool NetworkingServer::isClientConnected(const string& username) const
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::isClientConnected");
	}

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

	return false;
}

const string NetworkingServer::getNewClientIP() const
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getNewClientIP");
	}

	return _newClientIP;
}

const string NetworkingServer::getNewClientUsername() const
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getNewClientUsername");
	}

	return _newClientUsername;
}

const string NetworkingServer::getOldClientIP() const
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getOldClientIP");
	}

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
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getOldClientUsername");
	}

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
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getPendingMessages");
	}

	return _pendingMessages;
}

const vector<string> NetworkingServer::getClientIPs() const
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getClientIPs");
	}

	vector<string> clientIPs;
	for(size_t i = 0; i < _clientIPs.size(); i++)
	{
		// Check if client is found
		if(!_clientUsernames[i].empty())
		{
			clientIPs.push_back(_clientIPs[i]);
		}
	}

	return clientIPs;
}

const vector<string> NetworkingServer::getClientUsernames() const
{
	vector<string> clientUsernames;

	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::getClientUsernames");
	}

	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			clientUsernames.push_back(_clientUsernames[i]);
		}
	}

	return clientUsernames;
}

void NetworkingServer::sendTcpMessage(const string& username, const string& content)
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::sendTcpMessage::1");
	}

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

	Logger::throwError("NetworkingServer::sendTcpMessage::2");
}

void NetworkingServer::sendUdpMessage(const string& username, const string& content)
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::sendUdpMessage::1");
	}

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

	Logger::throwError("NetworkingServer::sendUdpMessage::2");
}

void NetworkingServer::broadcastTcpMessage(const string& content, const string& exceptionUsername)
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::broadcastTcpMessage");
	}

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
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::broadcastUdpMessage");
	}

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
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::disconnectClient::1");
	}

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

	Logger::throwError("NetworkingServer::disconnectClient::2");
}

void NetworkingServer::disconnectClients()
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::disconnectClients::1");
	}

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