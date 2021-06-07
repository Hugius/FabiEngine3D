#define WIN32_LEAN_AND_MEAN

#include "network_server_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkServerAPI::_sendTcpMessage(SOCKET clientSocketID, const string& content, bool isReserved)
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to send TCP message: not running!");
		return false;
	}

	// Validate message content
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking message tried to send TCP message: cannot contain semicolons!");
		return false;
	}
	else if (NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwWarning("Networking server tried to send TCP message: \"" + content + "\" is reserved!");
		return false;
	}
	else if (content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking server tried to send TCP message: maximum character amount exceeded!");
		return false;
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
			return false;
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking server TCP send failed with error code: ", WSAGetLastError());
		}
	}

	return true;
}

bool NetworkServerAPI::_sendUdpMessage(const string& clientIP, const string& clientPort, const string& content)
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking server tried to send UDP message: not running!");
		return false;
	}

	// Validate message content
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking message tried to send UDP message: cannot contain semicolons!");
		return false;
	}
	else if (NetworkUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking server tried to send UDP message: \"" + content + "\" is reserved!");
		return false;
	}
	else if (content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking server tried to send UDP message: maximum character amount exceeded!");
		return false;
	}

	// Compose socket address
	sockaddr_in targetAddress = sockaddr_in();
	targetAddress.sin_family = AF_INET;
	targetAddress.sin_addr.s_addr = inet_addr(clientIP.c_str());
	targetAddress.sin_port = htons(stoi(clientPort));

	// Send message to client
	auto sendStatusCode = sendto(
		_udpMessageSocketID, // UDP socket
		content.c_str(), // Message content
		static_cast<int>(content.size()), // Message size
		0, // Flags
		reinterpret_cast<sockaddr*>(&targetAddress), // Client address
		sizeof(targetAddress)); // Client address length

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking server UDP send failed with error code: ", WSAGetLastError());
	}

	return true;
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
	_clientMessageBuilds.push_back("");

	// Spawn thread for receiving TCP messages
	_tcpMessageThreads.push_back(std::async(std::launch::async, &NetworkServerAPI::_waitForTcpMessage, this, clientSocketID));
}

void NetworkServerAPI::_disconnectClient(SOCKET clientSocketID)
{
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Find list index
		if (clientSocketID == _clientSocketIDs[i])
		{
			// Temporarily save username
			auto clientUsername = _clientUsernames[i];

			// Close connection
			closesocket(clientSocketID);

			// Remove client data
			_clientSocketIDs.erase(_clientSocketIDs.begin() + i);
			_clientIPs.erase(_clientIPs.begin() + i);
			_clientPorts.erase(_clientPorts.begin() + i);
			_clientUsernames.erase(_clientUsernames.begin() + i);
			_clientMessageBuilds.erase(_clientMessageBuilds.begin() + i);
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

tuple<int, int, long long, string> NetworkServerAPI::_waitForTcpMessage(SOCKET clientSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::TCP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::TCP_BUFFER_BYTES);
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

tuple<int, int, long long, string> NetworkServerAPI::_receiveUdpMessage(SOCKET udpMessageSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::UDP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::UDP_BUFFER_BYTES);
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