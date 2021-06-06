#define WIN32_LEAN_AND_MEAN

#include "network_server_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkServerAPI::isRunning()
{
	return _isRunning;
}

bool NetworkServerAPI::isClientConnected(const string& username)
{
	// Check if server is even running
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

const vector<NetworkClientMessage>& NetworkServerAPI::getPendingMessages()
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to retrieve pending messages: not running!");
	}

	return _pendingMessages;
}

const vector<string> NetworkServerAPI::getClientIPs()
{
	// Check if server is even running
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
	// Check if server is even running
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
	// Check if server is even running
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

void NetworkServerAPI::sendMessageTCP(const string& username, const string& content)
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to send message: not running!");
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
				_sendMessageTCP(_clientSocketIDs[i], content, false);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwWarning("Networking server tried to send TCP message to client \"" + username + "\": not connected!");
}

void NetworkServerAPI::sendMessageUDP(const string& username, const string& content)
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to send TCP message: not running!");
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
				_sendMessageUDP(_clientIPs[i], _clientPorts[i], content);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwWarning("Networking server tried to send UDP message to client \"" + username + "\": not connected!");
}

void NetworkServerAPI::broadcastMessageTCP(const string& content)
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to broadcast TCP message: not running!");
	}

	// Send message to all connected clients
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Client must be fully accepted
		if (!_clientUsernames[i].empty())
		{
			_sendMessageTCP(_clientSocketIDs[i], content, false);
		}
	}
}

void NetworkServerAPI::broadcastMessageUDP(const string& content)
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to broadcast UDP message: not running!");
	}

	// Try to find client and send message
	for (size_t i = 0; i < _clientUsernames.size(); i++)
	{
		// Client must be fully accepted
		if (!_clientUsernames[i].empty())
		{
			_sendMessageUDP(_clientIPs[i], _clientPorts[i], content);
		}
	}
}

void NetworkServerAPI::disconnectClient(const string& username)
{
	// Check if server is even running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to disconnect client: not running!");
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
				_sendMessageTCP(_clientSocketIDs[i], "DISCONNECTED_BY_SERVER", true);
				_disconnectingClientSocketIDs.push_back(_clientSocketIDs[i]);
				return;
			}
		}
	}

	// Client not connected
	Logger::throwWarning("Networking server tried to disconnect client \"" + username + "\": not connected!");
}

void NetworkServerAPI::_sendMessageTCP(SOCKET clientSocketID, const string& content, bool isReserved)
{
	// Validate message semantics
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking message tried to send message: cannot contain semicolons!");
		return;
	}

	// Check if message is not reserved
	if (NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwWarning("Networking server tried to send message: \"" + content + "\" is reserved!");
		return;
	}

	// Add a semicolon to indicate end of this message
	string message = content + ';';

	// Send message to client
	auto sendStatusCode = send(clientSocketID, message.c_str(), static_cast<int>(message.size()), 0);

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED) // Client lost socket connection
		{
			_disconnectClient(clientSocketID);
		}
		else // Something really bad happened
		{
			Logger::throwError("Network server TCP send failed with error code: ", WSAGetLastError());
		}
	}
}

void NetworkServerAPI::_sendMessageUDP(const string& clientIP, const string& clientPort, const string& content)
{
	// Validate message semantics
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking message tried to send UDP message: cannot contain semicolons!");
		return;
	}

	// Check if message is not reserved
	if (NetworkUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking server tried to send UDP message: \"" + content + "\" is reserved!");
		return;
	}

	// Compose socket address
	sockaddr_in targetAddress;
	targetAddress.sin_family = AF_INET;
	targetAddress.sin_addr.s_addr = inet_addr(clientIP.c_str());
	targetAddress.sin_port = htons(stoi(clientPort));

	// Send message to client
	auto sendStatusCode = sendto(
		_udpMessageSocketID, // UDP socket
		content.c_str(), // Message
		static_cast<int>(content.size()), // Message size
		0, // Flags
		reinterpret_cast<sockaddr*>(&targetAddress), // Server address
		sizeof(targetAddress)); // Server address length

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Network server UDP send failed with error code: ", WSAGetLastError());
	}
}

void NetworkServerAPI::_acceptClient(SOCKET clientSocketID)
{
	// Extract IP & port
	auto clientIP = NetworkUtils::extractIP(clientSocketID);
	auto clientPort = NetworkUtils::extractPort(clientSocketID);

	// Save client data
	_clientSocketIDs.push_back(clientSocketID);
	_clientIPs.push_back(clientIP);
	_clientPorts.push_back(clientPort);
	_clientUsernames.push_back("");

	// Spawn thread for receiving TCP messages
	_tcpMessageThreads.push_back(std::async(std::launch::async, &NetworkServerAPI::_waitForClientMessageTCP, this, clientSocketID));
}

void NetworkServerAPI::_disconnectClient(SOCKET clientSocketID)
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
			_tcpMessageThreads.erase(_tcpMessageThreads.begin() + i);

			// Logging (if client was fully accepted)
			if (!clientUsername.empty())
			{
				Logger::throwInfo("Networking client \"" + clientUsername + "\" lost connection with the server!");
			}

			return;
		}
	}
}

SOCKET NetworkServerAPI::_waitForClientConnection(SOCKET listenSocketID)
{
	return accept(listenSocketID, nullptr, nullptr);
}

tuple<int, int, long long, string> NetworkServerAPI::_waitForClientMessageTCP(SOCKET clientSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::MAX_MESSAGE_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::MAX_MESSAGE_BYTES);
	auto receiveStatusCode = recv(clientSocketID, buffer, bufferLength, 0);

	if (receiveStatusCode > 0) // Message received correctly
	{
		return make_tuple(receiveStatusCode, 0, Tools::getTimeSinceEpochMS(), string(buffer, receiveStatusCode));
	}
	else if (receiveStatusCode == 0) // Client closed connection
	{
		return make_tuple(receiveStatusCode, 0, Tools::getTimeSinceEpochMS(), "");
	}
	else // Something else happened
	{
		return make_tuple(receiveStatusCode, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, long long, string> NetworkServerAPI::_receiveClientMessageUDP(SOCKET udpMessageSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::MAX_MESSAGE_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::MAX_MESSAGE_BYTES);
	auto receiveResult = recvfrom(udpMessageSocketID, buffer, bufferLength, 0, nullptr, nullptr);

	if (receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), string(buffer, receiveResult));
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}