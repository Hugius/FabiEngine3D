#include "network_server_api.hpp"
#include "logger.hpp"

bool NetworkServerAPI::isRunning()
{
	return _isRunning;
}

bool NetworkServerAPI::isClientConnected(const string& username)
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to retrieve client connection status: not running!");
	}

	// Try to find client
	for (size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if (!_clientUsernames[i].empty())
		{
			// Check if client is found
			if (username == _clientUsernames[i])
			{
				return true;
			}
		}
	}

	return false;
}

const string& NetworkServerAPI::getNewClientIP()
{
	return _newClientIP;
}

const string& NetworkServerAPI::getNewClientPort()
{
	return _newClientPort;
}

const string& NetworkServerAPI::getNewClientUsername()
{
	return _newClientUsername;
}

const string NetworkServerAPI::getOldClientIP()
{
	if (_oldClientIPs.empty())
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
	if (_oldClientPorts.empty())
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
	if (_oldClientUsernames.empty())
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
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to retrieve pending messages: not running!");
	}

	return _pendingMessages;
}

const vector<string> NetworkServerAPI::getClientIPs()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to retrieve client IPs: not running!");
	}

	// Client must be fully accepted
	vector<string> clientIPs;
	for (size_t i = 0; i < _clientIPs.size(); i++)
	{
		if (!_clientUsernames[i].empty())
		{
			clientIPs.push_back(_clientIPs[i]);
		}
	}
	return clientIPs;
}

const vector<string> NetworkServerAPI::getClientPorts()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to retrieve client ports: not running!");
	}

	// Client must be fully accepted
	vector<string> clientPorts;
	for (size_t i = 0; i < _clientPorts.size(); i++)
	{
		if (!_clientUsernames[i].empty())
		{
			clientPorts.push_back(_clientPorts[i]);
		}
	}
	return clientPorts;
}

const vector<string> NetworkServerAPI::getClientUsernames()
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to retrieve client usernames: not running!");
	}

	// Client must be fully accepted
	vector<string> clientUsernames;
	for (size_t i = 0; i < _clientUsernames.size(); i++)
	{
		if (!_clientUsernames[i].empty())
		{
			clientUsernames.push_back(_clientUsernames[i]);
		}
	}
	return clientUsernames;
}

void NetworkServerAPI::sendTcpMessage(const string& username, const string& content)
{
	// Try to find client and send message
	for (size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if (!_clientUsernames[i].empty())
		{
			// Check if client is found
			if (username == _clientUsernames[i])
			{
				// Send message
				_sendTcpMessage(_clientSocketIDs[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwWarning("Networking server tried to send TCP message to client \"" + username + "\": not connected!");
}

void NetworkServerAPI::sendUdpMessage(const string& username, const string& content)
{
	// Try to find client and send message
	for (size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if (!_clientUsernames[i].empty())
		{
			// Check if client is found
			if (username == _clientUsernames[i])
			{
				// Send message
				_sendUdpMessage(_clientIPs[i], _clientPorts[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwWarning("Networking server tried to send UDP message to client \"" + username + "\": not connected!");
}

void NetworkServerAPI::broadcastTcpMessage(const string& content, const string& exceptionUsername)
{
	// Send message to all connected clients
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Check exception
		if (_clientUsernames[i] != exceptionUsername)
		{
			// Client must be fully accepted
			if (!_clientUsernames[i].empty())
			{
				// Send message
				_sendTcpMessage(_clientSocketIDs[i], content, false);
			}
		}
	}
}

void NetworkServerAPI::broadcastUdpMessage(const string& content, const string& exceptionUsername)
{
	// Try to find client and send message
	for (size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Check exception
		if (_clientUsernames[i] != exceptionUsername)
		{
			// Client must be fully accepted
			if (!_clientUsernames[i].empty())
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
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to disconnect client \"" + username + "\": not running!");
	}

	// Try to find client and send message
	for (size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if (!_clientUsernames[i].empty())
		{
			// Check if client is found
			if (username == _clientUsernames[i])
			{
				// Notify & disconnect client
				_sendTcpMessage(_clientSocketIDs[i], "DISCONNECTED_BY_SERVER", true);
				_disconnectingClientSocketIDs.push_back(_clientSocketIDs[i]);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwWarning("Networking server tried to disconnect client \"" + username + "\": not connected!");
}