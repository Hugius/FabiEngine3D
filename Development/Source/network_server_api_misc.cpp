#define WIN32_LEAN_AND_MEAN

#include "network_server_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::launch;

bool NetworkServerAPI::_sendTcpMessage(SOCKET clientSocketID, const string& content, bool isReserved)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::_sendTcpMessage::1");
	}

	// Validate message content
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkServerAPI::_sendTcpMessage::2");
	}
	else if(NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkServerAPI::_sendTcpMessage::3");
	}
	else if(content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkServerAPI::_sendTcpMessage::4");
	}

	// Add a semicolon to indicate end of this message
	string message = (content + ';');

	// Send message to client
	auto sendStatusCode = send(clientSocketID, message.c_str(), static_cast<int>(message.size()), 0);

	// Check if sending went wrong
	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED) // Client lost socket connection
		{
			_disconnectClient(clientSocketID);
			return false;
		}
		else if(WSAGetLastError() == WSAENOBUFS) // Buffer full
		{
			Logger::throwWarning("Networking server is sending too many TCP messages!");
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkServerAPI::_sendTcpMessage::5 ---> ", WSAGetLastError());
		}
	}

	return true;
}

bool NetworkServerAPI::_sendUdpMessage(const string& clientIP, const string& clientPort, const string& content, bool isReserved)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkServerAPI::_sendUdpMessage::1");
	}

	// Validate message content
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkServerAPI::_sendUdpMessage::2");
	}
	else if(NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkServerAPI::_sendUdpMessage::3");
	}
	else if(content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkServerAPI::_sendUdpMessage::4");
	}

	// Compose socket address
	auto socketAddress = NetworkUtils::composeSocketAddress(clientIP, clientPort);

	// Send message to client
	auto sendStatusCode = sendto(
		_udpSocketID, // UDP socket
		content.c_str(), // Message content
		static_cast<int>(content.size()), // Message size
		0, // Flags
		reinterpret_cast<sockaddr*>(&socketAddress), // Client address
		sizeof(socketAddress)); // Client address length

	// Check if sending went wrong
	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAENOBUFS) // Buffer full
		{
			Logger::throwWarning("Networking server is sending too many UDP messages!");
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkServerAPI::_sendUdpMessage::5 ---> ", WSAGetLastError());
		}
	}

	return true;
}

bool NetworkServerAPI::_isClientConnected(const string& IP, const string& port)
{
	bool foundIP = (find(_clientIPs.begin(), _clientIPs.end(), IP) != _clientIPs.end());
	bool foundPort = (find(_clientPorts.begin(), _clientPorts.end(), port) != _clientPorts.end());
	return (foundIP && foundPort);
}

void NetworkServerAPI::_disconnectClient(SOCKET clientSocketID)
{
	for(size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Find list index
		if(clientSocketID == _clientSocketIDs[i])
		{
			// Temporarily save username
			auto clientUsername = _clientUsernames[i];

			// Close socket
			closesocket(clientSocketID);

			// Save disonnected client data
			_oldClientIPs.push_back(_clientIPs[i]);
			_oldClientPorts.push_back(_clientPorts[i]);
			_oldClientUsernames.push_back(_clientUsernames[i]);

			// Remove client data
			_clientSocketIDs.erase(_clientSocketIDs.begin() + i);
			_clientIPs.erase(_clientIPs.begin() + i);
			_clientPorts.erase(_clientPorts.begin() + i);
			_clientUsernames.erase(_clientUsernames.begin() + i);
			_clientTcpMessageBuilds.erase(_clientTcpMessageBuilds.begin() + i);
			_tcpMessageThreads.erase(_tcpMessageThreads.begin() + i);

			// Logging (if client was fully accepted)
			if(!clientUsername.empty())
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

tuple<int, int, long long, string> NetworkServerAPI::_waitForTcpMessage(SOCKET clientSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::TCP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::TCP_BUFFER_BYTES);
	auto receiveStatusCode = recv(clientSocketID, buffer, bufferLength, 0);

	if(receiveStatusCode > 0) // Message received correctly
	{
		return make_tuple(receiveStatusCode, 0, Tools::getTimeSinceEpochMS(), string(buffer, receiveStatusCode));
	}
	else if(receiveStatusCode == 0) // Client closed connection
	{
		return make_tuple(receiveStatusCode, 0, Tools::getTimeSinceEpochMS(), "");
	}
	else // Something else happened
	{
		return make_tuple(receiveStatusCode, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, string, string, string> NetworkServerAPI::_receiveUdpMessage(SOCKET udpMessageSocketID)
{
	// Data store
	char buffer[NetworkUtils::UDP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::UDP_BUFFER_BYTES);
	sockaddr_in sourceAddress = sockaddr_in();
	int sourceAddressLength = sizeof(sourceAddress);

	// Receive data
	auto receiveResult = recvfrom(udpMessageSocketID, buffer, bufferLength, 0, reinterpret_cast<sockaddr*>(&sourceAddress), &sourceAddressLength);

	// Extract address
	auto IP = NetworkUtils::extractAddressIP(&sourceAddress);
	auto port = NetworkUtils::extractAddressPort(&sourceAddress);

	if(receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), string(buffer, receiveResult), IP, port);
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), "", IP, port);
	}
}