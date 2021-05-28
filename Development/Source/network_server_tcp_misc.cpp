#define WIN32_LEAN_AND_MEAN

#include "network_server_tcp.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkServerTCP::isRunning()
{
	return _isRunning;
}

const vector<NetworkMessage>& NetworkServerTCP::getReceivedMessages()
{
	return _receivedMessages;
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

	Logger::throwWarning("Cannot send message to client \"" + message.ipAddress + ":" + message.port + "\"!");
}

void NetworkServerTCP::broadcastMessage(const string& content)
{
	for (auto& socketID : _clientSocketIDs)
	{
		_sendMessage(socketID, content);
	}
}

void NetworkServerTCP::_sendMessage(SOCKET clientSocketID, const string& content)
{
	auto sendStatusCode = send(clientSocketID, content.c_str(), static_cast<int>(content.size()), 0);

	if (sendStatusCode == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAECONNRESET) // Client lost socket connection
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
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(clientSocketID, (struct sockaddr*)&socketAddress, &socketAddressLength);
	auto ipAddress = string(inet_ntoa(socketAddress.sin_addr));
	auto port = std::to_string(socketAddress.sin_port);

	// Save client data
	_clientSocketIDs.push_back(clientSocketID);
	_clientIPs.push_back(ipAddress);
	_clientPorts.push_back(port);

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
			auto ipAddress = _clientIPs[i];
			auto port = _clientPorts[i];

			// Close connection
			closesocket(_clientSocketIDs[i]);

			// Remove client data
			_clientSocketIDs.erase(_clientSocketIDs.begin() + i);
			_clientIPs.erase(_clientIPs.begin() + i);
			_clientPorts.erase(_clientPorts.begin() + i);
			_messageThreads.erase(_messageThreads.begin() + i);

			// Notify logger
			Logger::throwInfo("Networking client \"" + ipAddress + ":" + port + "\" lost connection with the server!");
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
	char buffer[MAX_MESSAGE_BYTES];
	int bufferLength = MAX_MESSAGE_BYTES;
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