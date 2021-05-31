#define WIN32_LEAN_AND_MEAN

#include "network_server_tcp.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkServerTCP::isRunning()
{
	return _isRunning;
}

bool NetworkServerTCP::isClientConnected(const string& username)
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server must be running before retrieving client connection status!");
		return false;
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

const vector<NetworkMessage>& NetworkServerTCP::getPendingMessages()
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server must be running before retrieving pending messages!");
	}

	return _pendingMessages;
}

const vector<string> NetworkServerTCP::getClientIPs()
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server must be running before retrieving client IPs!");
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

const vector<string> NetworkServerTCP::getClientPorts()
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server must be running before retrieving client ports!");
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

const vector<string> NetworkServerTCP::getClientUsernames()
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server must be running before retrieving client usernames!");
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

void NetworkServerTCP::sendMessage(const string& username, const string& content)
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server must be running before sending messages!");
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
				_sendMessage(_clientSocketIDs[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwWarning("Networking server cannot send message to client \"" + username + "\": not connected!");
}

void NetworkServerTCP::broadcastMessage(const string& content)
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server must be running before broadcasting messages!");
	}

	// Send message to all connected clients
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Client must be fully accepted
		if (!_clientUsernames[i].empty())
		{
			_sendMessage(_clientSocketIDs[i], content, false);
		}
	}
}

void NetworkServerTCP::disconnectClient(const string& username)
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server must be running before disconnecting clients!");
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
				_disconnectClient(_clientSocketIDs[i]);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwWarning("Networking server cannot disconnect client \"" + username + "\": not connected!");
}

void NetworkServerTCP::_sendMessage(SOCKET clientSocketID, const string& content, bool isReserved)
{
	// Validate message semantics
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking message cannot contain semicolons!");
		return;
	}

	// Check if message is not reserved
	if (NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwWarning("Networking message \"" + content + "\" is reserved!");
		return;
	}

	// Add a semicolon to indicate end of this message
	string messageContent = content + ';';
	auto sendStatusCode = send(clientSocketID, messageContent.c_str(), static_cast<int>(messageContent.size()), 0);

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED) // Client lost socket connection
		{
			_disconnectClient(clientSocketID);
		}
		else // Something really bad happened
		{
			Logger::throwError("Network server send failed with error code: ", WSAGetLastError());
		}
	}
}

void NetworkServerTCP::_acceptClient(SOCKET clientSocketID)
{
	// Extract IP address & port
	auto clientIP = NetworkUtils::extractIP(clientSocketID);
	auto clientPort = NetworkUtils::extractPort(clientSocketID);

	// Save client data
	_clientSocketIDs.push_back(clientSocketID);
	_clientIPs.push_back(clientIP);
	_clientPorts.push_back(clientPort);
	_clientUsernames.push_back("");

	// Spawn thread for receiving messages
	_messageThreads.push_back(std::async(std::launch::async, &NetworkServerTCP::_waitForClientMessage, this, clientSocketID));
}

void NetworkServerTCP::_disconnectClient(SOCKET clientSocketID)
{
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Find list index
		if (clientSocketID == _clientSocketIDs[i])
		{
			// Temporary values
			auto clientUsername = _clientUsernames[i];

			// Close connection
			closesocket(clientSocketID);

			// Remove client data
			_clientSocketIDs.erase(_clientSocketIDs.begin() + i);
			_clientIPs.erase(_clientIPs.begin() + i);
			_clientPorts.erase(_clientPorts.begin() + i);
			_clientUsernames.erase(_clientUsernames.begin() + i);
			_messageThreads.erase(_messageThreads.begin() + i);

			// Logging (if client was fully accepted)
			if (!clientUsername.empty())
			{
				Logger::throwInfo("Networking client \"" + clientUsername + "\" lost connection with the server!");
			}

			return;
		}
	}
}

SOCKET NetworkServerTCP::_waitForClientConnection(SOCKET listenSocketID)
{
	return accept(listenSocketID, nullptr, nullptr);
}

tuple<int, int, string> NetworkServerTCP::_waitForClientMessage(SOCKET clientSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::MAX_MESSAGE_BYTES];
	int bufferLength = NetworkUtils::MAX_MESSAGE_BYTES;
	auto receiveStatusCode = recv(clientSocketID, buffer, bufferLength, 0);

	if (receiveStatusCode > 0) // Message received correctly
	{
		return make_tuple(receiveStatusCode, 0, string(buffer, receiveStatusCode));
	}
	else if (receiveStatusCode == 0) // Client closed connection
	{
		return make_tuple(receiveStatusCode, 0, "");
	}
	else // Something else happened
	{
		return make_tuple(receiveStatusCode, WSAGetLastError(), "");
	}
}