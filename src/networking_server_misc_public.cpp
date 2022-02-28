#include "networking_server.hpp"
#include "logger.hpp"

const bool NetworkingServer::isRunning() const
{
	return _isRunning;
}

const bool NetworkingServer::isClientConnected(const string& username) const
{
	for(unsigned int i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			if(username == _clientUsernames[i])
			{
				return true;
			}
		}
	}

	return false;
}

const string NetworkingServer::getNewClientIp() const
{
	return _newClientIp;
}

const string NetworkingServer::getNewClientUsername() const
{
	return _newClientUsername;
}

const string NetworkingServer::getOldClientIp() const
{
	if(_oldClientIps.empty())
	{
		return "";
	}
	else
	{
		return _oldClientIps[0];
	}
}

const string NetworkingServer::getOldClientUsername() const
{
	if(_oldClientUsernames.empty())
	{
		return "";
	}
	else
	{
		return _oldClientUsernames[0];
	}
}

const unsigned int NetworkingServer::getMaxMessageSize() const
{
	return MAX_MESSAGE_SIZE;
}

const vector<NetworkingClientMessage>& NetworkingServer::getPendingMessages() const
{
	return _pendingMessages;
}

const vector<string> NetworkingServer::getClientIps() const
{
	vector<string> result;

	for(unsigned int i = 0; i < _clientIps.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			result.push_back(_clientIps[i]);
		}
	}

	return result;
}

const vector<string> NetworkingServer::getClientUsernames() const
{
	vector<string> clientUsernames;

	for(unsigned int i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			clientUsernames.push_back(_clientUsernames[i]);
		}
	}

	return clientUsernames;
}

void NetworkingServer::sendTcpMessageToClient(const string& username, const string& content)
{
	if(!_isRunning)
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

	for(unsigned int i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			if(username == _clientUsernames[i])
			{
				_sendTcpMessageToClient(_clientSockets[i], content, false);
				return;
			}
		}
	}

	abort();
}

void NetworkingServer::sendUdpMessageToClient(const string& username, const string& content)
{
	if(!_isRunning)
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

	for(unsigned int i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			if(username == _clientUsernames[i])
			{
				_sendUdpMessageToClient(_clientIps[i], _udpClientPorts[i], content, false);
				return;
			}
		}
	}

	abort();
}

void NetworkingServer::broadcastTcpMessageToClients(const string& content)
{
	if(!_isRunning)
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

	for(unsigned int i = 0; i < _clientSockets.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			_sendTcpMessageToClient(_clientSockets[i], content, false);
		}
	}
}

void NetworkingServer::broadcastUdpMessageToClients(const string& content)
{
	if(!_isRunning)
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

	for(unsigned int i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			_sendUdpMessageToClient(_clientIps[i], _udpClientPorts[i], content, false);
		}
	}
}

void NetworkingServer::disconnectClient(const string& username)
{
	if(!_isRunning)
	{
		abort();
	}

	for(unsigned int i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			if(username == _clientUsernames[i])
			{
				_sendTcpMessageToClient(_clientSockets[i], "DISCONNECTED", true);
				return;
			}
		}
	}

	abort();
}

void NetworkingServer::disconnectClients()
{
	if(!_isRunning)
	{
		abort();
	}

	for(unsigned int i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			_sendTcpMessageToClient(_clientSockets[i], "DISCONNECTED", true);
			return;
		}
	}
}