#define WIN32_LEAN_AND_MEAN

#include "network_server_tcp.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

void NetworkServerTCP::update()
{
	// Must be running first
	if (!_isRunning)
	{
		return;
	}

	// Clear all received messages from last frame
	_pendingMessages.clear();

	// Close rejected client connections
	if (_rejectedClientSocketID != INVALID_SOCKET)
	{
		closesocket(_rejectedClientSocketID);
		_rejectedClientSocketID = INVALID_SOCKET;
	}

	// Handle new client connections
	if (_connectionThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
	{
		// Retrieve new client socket ID
		auto clientSocketID = _connectionThread.get();
		if (clientSocketID == INVALID_SOCKET)
		{
			Logger::throwError("Networking server accept failed with error code: ", WSAGetLastError());
		}

		// Check if client is allowed to connect
		if (_clientIPs.size() == NetworkUtils::MAX_CLIENT_COUNT || _clientIPs.size() == _customMaxClientCount)
		{
			// Reject client
			_sendMessage(clientSocketID, "SERVER_FULL");
			_rejectedClientSocketID = clientSocketID;

			// Extract IP address & port
			auto clientIP = NetworkUtils::extractIP(clientSocketID);
			auto clientPort = NetworkUtils::extractPort(clientSocketID);

			// Logging
			Logger::throwInfo("Networking client \"" + clientIP + ":" + clientPort + "\" tried to connect to the server: SERVER_FULL!");
		}
		else
		{
			// Save new client
			_acceptClient(clientSocketID);

			// Logging
			Logger::throwInfo("Networking client \"" + _clientIPs.back() + ":" + _clientPorts.back() + "\" connected to the server!");
		}

		// Spawn connection thread again for next possible client
		_connectionThread = std::async(std::launch::async, &NetworkServerTCP::_waitForClientConnection, this, _connectionSocketID);
	}

	// Receive incoming client messages
BEGIN:
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Temporary values
		auto clientSocketID = _clientSocketIDs[i];
		auto clientIP = _clientIPs[i];
		auto clientPort = _clientPorts[i];
		auto& messageThread = _messageThreads[i];

		// Check if the client sent any message
		if (messageThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			// Temporary values
			auto messageResult = messageThread.get();
			auto messageStatusCode = std::get<0>(messageResult);
			auto messageErrorCode = std::get<1>(messageResult);
			auto messageContent = std::get<2>(messageResult);

			if (messageStatusCode > 0) // Message is received correctly
			{
				// Loop through received message(s)
				for (const auto& character : messageContent)
				{
					if (character == ';') // End of current message
					{
						if (_currentMessageBuild == "PING") // Handle ping response
						{
							_sendMessage(clientSocketID, "PING");
							_currentMessageBuild = "";
						}
						else // Handle other messages
						{
							_pendingMessages.push_back(NetworkMessage(clientIP, clientPort, _currentMessageBuild));
							_currentMessageBuild = "";
						}
					}
					else // Add to current message
					{
						_currentMessageBuild += character;
					}
				}
			}
			else if (messageStatusCode == 0) // Client closed socket connection
			{
				_disconnectClient(clientSocketID);
				goto BEGIN;
			}
			else // Receive failed
			{
				if (messageErrorCode == WSAECONNRESET) // Client lost socket connection
				{
					_disconnectClient(clientSocketID);
					goto BEGIN;
				}
				else // Something really bad happened
				{
					Logger::throwError("Networking server receive failed with error code: ", messageErrorCode);
				}
			}

			// Spawn new message thread
			messageThread = std::async(std::launch::async, &NetworkServerTCP::_waitForClientMessage, this, clientSocketID);
		}
	}
}