#define WIN32_LEAN_AND_MEAN

#include "network_server_tcp.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkServerTCP::isRunning()
{
	return _isRunning;
}

bool NetworkServerTCP::isClientConnected(const string& ipAddress, const string& port)
{
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		if (ipAddress == _clientIPs[i] && port == _clientPorts[i])
		{
			return true;
		}
	}

	return false;
}

const vector<NetworkMessage>& NetworkServerTCP::getPendingMessages()
{
	return _pendingMessages;
}

const vector<string>& NetworkServerTCP::getClientIPs()
{
	return _clientIPs;
}

const vector<string>& NetworkServerTCP::getClientPorts()
{
	return _clientPorts;
}

void NetworkServerTCP::sendMessage(const NetworkMessage& message)
{
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		if (message.ipAddress == _clientIPs[i] && message.port == _clientPorts[i])
		{
			_sendMessage(_clientSocketIDs[i], message.content);
			return;
		}
	}

	Logger::throwWarning("Networking server cannot send message to client \"" + message.ipAddress + ":" + message.port + "\": not connected!");
}

void NetworkServerTCP::broadcastMessage(const string& content)
{
	for (const auto& socketID : _clientSocketIDs)
	{
		_sendMessage(socketID, content);
	}
}

void NetworkServerTCP::_sendMessage(SOCKET clientSocketID, const string& content)
{
	// Validate message semantics
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking message cannot contain semicolons!");
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
			auto clientIP = _clientIPs[i];
			auto clientPort = _clientPorts[i];

			// Close connection
			closesocket(clientSocketID);

			// Remove client data
			_clientSocketIDs.erase(_clientSocketIDs.begin() + i);
			_clientIPs.erase(_clientIPs.begin() + i);
			_clientPorts.erase(_clientPorts.begin() + i);
			_messageThreads.erase(_messageThreads.begin() + i);

			// Logging
			Logger::throwInfo("Networking client \"" + clientIP + ":" + clientPort + "\" lost connection with the server!");
			break;
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