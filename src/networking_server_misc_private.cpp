#define WIN32_LEAN_AND_MEAN

#include "networking_server.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::launch;

const bool NetworkingServer::_sendTcpMessage(SOCKET socket, const string& content, bool isReserved)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::_sendTcpMessage::1");
	}

	// Validate message content
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkingServer::_sendTcpMessage::2");
	}
	else if(NetworkingUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkingServer::_sendTcpMessage::3");
	}
	else if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkingServer::_sendTcpMessage::4");
	}

	// Add a semicolon to indicate end of this message
	string message = (content + ';');

	// Send message to client
	auto sendStatusCode = send(socket, message.c_str(), static_cast<int>(message.size()), 0);

	// Check if sending went wrong
	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED) // Client lost socket connection
		{
			_disconnectClient(socket);
			return false;
		}
		else if(WSAGetLastError() == WSAENOBUFS) // Buffer full
		{
			Logger::throwWarning("Networking server is sending too many TCP messages!");
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkingServer::_sendTcpMessage::5 ---> ", WSAGetLastError());
		}
	}

	return true;
}

const bool NetworkingServer::_sendUdpMessage(const string& clientIP, const string& clientPort, const string& content, bool isReserved) const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::_sendUdpMessage::1");
	}

	// Validate message content
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkingServer::_sendUdpMessage::2");
	}
	else if(NetworkingUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkingServer::_sendUdpMessage::3");
	}
	else if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkingServer::_sendUdpMessage::4");
	}

	// Compose socket address
	auto socketAddress = NetworkingUtils::composeSocketAddress(clientIP, clientPort);

	// Send message to client
	auto sendStatusCode = sendto(
		_udpSocket, // UDP socket
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
			Logger::throwError("NetworkingServer::_sendUdpMessage::5 ---> ", WSAGetLastError());
		}
	}

	return true;
}

void NetworkingServer::_disconnectClient(SOCKET socket)
{
	for(size_t i = 0; i < _clientSockets.size(); i++)
	{
		// Find list index
		if(socket == _clientSockets[i])
		{
			// Temporarily save username
			auto clientUsername = _clientUsernames[i];

			// Close socket
			closesocket(socket);

			// Save disonnected client data
			_oldClientIPs.push_back(_clientIPs[i]);
			_oldClientUsernames.push_back(_clientUsernames[i]);

			// Remove client data
			_clientSockets.erase(_clientSockets.begin() + i);
			_clientIPs.erase(_clientIPs.begin() + i);
			_tcpClientPorts.erase(_tcpClientPorts.begin() + i);
			_udpClientPorts.erase(_udpClientPorts.begin() + i);
			_clientUsernames.erase(_clientUsernames.begin() + i);
			_tcpMessageBuilds.erase(_tcpMessageBuilds.begin() + i);
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

const SOCKET NetworkingServer::_waitForClientConnection(SOCKET socket) const
{
	return accept(socket, nullptr, nullptr);
}

tuple<int, int, long long, string> NetworkingServer::_waitForTcpMessage(SOCKET socket) const
{
	// Retrieve bytes & size
	char buffer[NetworkingUtils::TCP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkingUtils::TCP_BUFFER_BYTES);
	auto receiveStatusCode = recv(socket, buffer, bufferLength, 0);

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

tuple<int, int, string, string, string> NetworkingServer::_receiveUdpMessage(SOCKET socket) const
{
	// Data store
	char buffer[NetworkingUtils::UDP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkingUtils::UDP_BUFFER_BYTES);
	sockaddr_in sourceAddress = sockaddr_in();
	int sourceAddressLength = sizeof(sourceAddress);

	// Receive data
	auto receiveResult = recvfrom(socket, buffer, bufferLength, 0, reinterpret_cast<sockaddr*>(&sourceAddress), &sourceAddressLength);

	// Extract address
	auto IP = NetworkingUtils::extractAddressIP(&sourceAddress);
	auto port = NetworkingUtils::extractAddressPort(&sourceAddress);

	if(receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), string(buffer, receiveResult), IP, port);
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), "", IP, port);
	}
}