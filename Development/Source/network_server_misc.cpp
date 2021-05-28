#include "network_server.hpp"
#define WIN32_LEAN_AND_MEAN

#include "network_server.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkServer::isRunning()
{
	return _isRunning;
}

bool NetworkServer::isMessagePending()
{
	return !_receivedMessageQueue.empty();
}

void NetworkServer::loadNextPendingMessage()
{
	if (_receivedMessageQueue.empty())
	{
		Logger::throwWarning("Cannot load next network message: no messages pending!");
	}
	else
	{
		_receivedMessageQueue.erase(_receivedMessageQueue.begin());
	}
}

const shared_ptr<NetworkMessage> NetworkServer::getPendingMessage()
{
	if (_receivedMessageQueue.empty())
	{
		Logger::throwWarning("Cannot retrieve network message: no messages pending!");
		return nullptr;
	}
	else
	{
		return _receivedMessageQueue.front();
	}
}

void NetworkServer::sendMessage(const string& ipAddress, const string& port, const string& content)
{
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		if (ipAddress == _clientIPs[i] && port == _clientPorts[i])
		{
			_sendMessage(_clientSocketIDs[i], content);
			return;
		}
	}

	Logger::throwWarning("Cannot send message to client: ip address not connected!"); // <-----
}

void NetworkServer::broadcastMessage(const string& content)
{
	for (auto& socketID : _clientSocketIDs)
	{
		_sendMessage(socketID, content);
	}
}

void NetworkServer::_sendMessage(SOCKET clientSocketID, const string& content)
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

void NetworkServer::_acceptClient(SOCKET clientSocketID)
{
	// Extract IP address
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(clientSocketID, (struct sockaddr*)&socketAddress, &socketAddressLength);
	auto ipAddress = string(inet_ntoa(socketAddress.sin_addr));
	auto port = std::to_string(socketAddress.sin_port);

	// Add client
	_clientSocketIDs.push_back(clientSocketID);
	_clientIPs.push_back(ipAddress);
	_clientPorts.push_back(port);
	_messageThreads.push_back(std::async(std::launch::async, &NetworkServer::_waitForClientMessage, this, clientSocketID));
}

void NetworkServer::_disconnectClient(SOCKET clientSocketID)
{
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		if (clientSocketID == _clientSocketIDs[i])
		{
			auto ipAddress = _clientIPs[i];

			closesocket(_clientSocketIDs[i]);
			_clientSocketIDs.erase(_clientSocketIDs.begin() + i);
			_clientIPs.erase(_clientIPs.begin() + i);
			_clientPorts.erase(_clientPorts.begin() + i);
			_messageThreads.erase(_messageThreads.begin() + i);

			Logger::throwInfo("Networking client with IP \"" + ipAddress + "\" lost connection with the server!");
			break;
		}
	}
}

SOCKET NetworkServer::_waitForClientConnection(SOCKET listenSocketID)
{
	return accept(listenSocketID, nullptr, nullptr);
}

tuple<int, string, int> NetworkServer::_waitForClientMessage(SOCKET clientSocketID)
{
	// Retrieve bytes & size
	char buffer[MAX_MESSAGE_BYTES];
	int bufferLength = MAX_MESSAGE_BYTES;
	auto receiveResult = recv(clientSocketID, buffer, bufferLength, 0);

	if (receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, string(buffer, receiveResult), WSAGetLastError());
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, "", WSAGetLastError());
	}
}