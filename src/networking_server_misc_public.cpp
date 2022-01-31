#include "networking_server.hpp"
#include "logger.hpp"

const bool NetworkingServer::isRunning() const
{
	return _isRunning;
}

const bool NetworkingServer::isClientConnected(const string& username) const
{
	for(size_t i = 0; i < _clientUsernames.size(); i++)
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

const string NetworkingServer::getNewClientIP() const
{
	return _newClientIP;
}

const string NetworkingServer::getNewClientUsername() const
{
	return _newClientUsername;
}

const string NetworkingServer::getOldClientIP() const
{
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

const vector<string> NetworkingServer::getClientIPs() const
{
	vector<string> result;

	for(size_t i = 0; i < _clientIPs.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			result.push_back(_clientIPs[i]);
		}
	}

	return result;
}

const vector<string> NetworkingServer::getClientUsernames() const
{
	vector<string> clientUsernames;

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

	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			if(username == _clientUsernames[i])
			{
				_sendTcpMessage(_clientSockets[i], content, false);
				return;
			}
		}
	}

	abort();
}

void NetworkingServer::sendUdpMessage(const string& username, const string& content)
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

	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			if(username == _clientUsernames[i])
			{
				_sendUdpMessage(_clientIPs[i], _udpClientPorts[i], content, false);
				return;
			}
		}
	}

	abort();
}

void NetworkingServer::broadcastTcpMessage(const string& content)
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

	for(size_t i = 0; i < _clientSockets.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			_sendTcpMessage(_clientSockets[i], content, false);
		}
	}
}

void NetworkingServer::broadcastUdpMessage(const string& content)
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

	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			_sendUdpMessage(_clientIPs[i], _udpClientPorts[i], content, false);
		}
	}
}

void NetworkingServer::disconnectClient(const string& username)
{
	if(!_isRunning)
	{
		abort();
	}

	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			if(username == _clientUsernames[i])
			{
				_sendTcpMessage(_clientSockets[i], "DISCONNECTED", true);
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

	for(size_t i = 0; i < _clientUsernames.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			_sendTcpMessage(_clientSockets[i], "DISCONNECTED", true);
			return;
		}
	}
}