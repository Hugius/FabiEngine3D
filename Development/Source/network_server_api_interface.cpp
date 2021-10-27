#include "network_server_api.hpp"
#include "logger.hpp"

bool NetworkServerAPI::isRunning()
{
	return _isRunning;
}

bool NetworkServerAPI::isClientConnected(const string& username)
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

	return false;
}

const string& NetworkServerAPI::getNewClientIP()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getNewClientIP");
	}

	return _newClientIP;
}

const string& NetworkServerAPI::getNewClientPort()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getNewClientPort");
	}

	return _newClientPort;
}

const string& NetworkServerAPI::getNewClientUsername()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getNewClientUsername");
	}

	return _newClientUsername;
}

const string NetworkServerAPI::getOldClientIP()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getOldClientIP");
	}

	if(_oldClientIPs.empty())
	{
		return "";
	}
	else
	{
		return _oldClientIPs.front();
	}
}

const string NetworkServerAPI::getOldClientPort()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getOldClientPort");
	}

	if(_oldClientPorts.empty())
	{
		return "";
	}
	else
	{
		return _oldClientPorts.front();
	}
}

const string NetworkServerAPI::getOldClientUsername()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getOldClientUsername");
	}

	if(_oldClientUsernames.empty())
	{
		return "";
	}
	else
	{
		return _oldClientUsernames.front();
	}
}

const vector<NetworkClientMessage>& NetworkServerAPI::getPendingMessages()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getPendingMessages");
	}

	return _pendingMessages;
}

const vector<string> NetworkServerAPI::getClientIPs()
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
		if(!_clientUsernames[i].empty())
		{
			clientIPs.push_back(_clientIPs[i]);
		}
	}
	return clientIPs;
}

const vector<string> NetworkServerAPI::getClientPorts()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getClientPorts");
	}

	// Client must be fully accepted
	vector<string> clientPorts;
	for(size_t i = 0; i < _clientPorts.size(); i++)
	{
		if(!_clientUsernames[i].empty())
		{
			clientPorts.push_back(_clientPorts[i]);
		}
	}
	return clientPorts;
}

const vector<string> NetworkServerAPI::getClientUsernames()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::getClientUsernames");
	}

	// Client must be fully accepted
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

void NetworkServerAPI::sendTcpMessage(const string& username, const string& content)
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
				// Send message
				_sendTcpMessage(_clientSocketIDs[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwError("NetworkServerAPI::sendTcpMessage::2");
}

void NetworkServerAPI::sendUdpMessage(const string& username, const string& content)
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
				// Send message
				_sendUdpMessage(_clientIPs[i], _clientPorts[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwError("NetworkServerAPI::sendUdpMessage::2");
}

void NetworkServerAPI::broadcastTcpMessage(const string& content, const string& exceptionUsername)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::broadcastTcpMessage");
	}

	// Send message to all connected clients
	for(size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Check exception
		if(_clientUsernames[i] != exceptionUsername)
		{
			// Client must be fully accepted
			if(!_clientUsernames[i].empty())
			{
				// Send message
				_sendTcpMessage(_clientSocketIDs[i], content, false);
			}
		}
	}
}

void NetworkServerAPI::broadcastUdpMessage(const string& content, const string& exceptionUsername)
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
				// Send message
				_sendUdpMessage(_clientIPs[i], _clientPorts[i], content, false);
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
				// Notify client
				_sendTcpMessage(_clientSocketIDs[i], "DISCONNECTED_BY_SERVER", true);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwError("NetworkServerAPI::disconnectClient::2");
}