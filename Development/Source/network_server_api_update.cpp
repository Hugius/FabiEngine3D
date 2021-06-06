#define WIN32_LEAN_AND_MEAN

#include "network_server_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

void NetworkServerAPI::update()
{
	// Must be running first
	if (!_isRunning)
	{
		return;
	}

	// Clear all received messages from last frame
	_pendingMessages.clear();

	// Close rejected client connections
	for (auto& socketID : _disconnectingClientSocketIDs)
	{
		if (std::find(_clientSocketIDs.begin(), _clientSocketIDs.end(), socketID) == _clientSocketIDs.end()) // Not connected yet
		{
			closesocket(socketID);
		}
		else // Was already a connected client
		{
			_disconnectClient(socketID);
		};
	}
	_disconnectingClientSocketIDs.clear();

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
			_sendMessageTCP(clientSocketID, "SERVER_FULL", true);
			_disconnectingClientSocketIDs.push_back(clientSocketID);
		}
		else
		{
			// Save new client
			_acceptClient(clientSocketID);
		}

		// Spawn connection thread again for next possible client
		_connectionThread = std::async(std::launch::async, &NetworkServerAPI::_waitForClientConnection, this, _connectionSocketID);
	}

	// Receive incoming TCP messages
BEGIN:
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Temporary values
		auto clientSocketID = _clientSocketIDs[i];
		auto clientIP = _clientIPs[i];
		auto clientPort = _clientPorts[i];
		auto& clientUsername = _clientUsernames[i];
		auto& messageThread = _tcpMessageThreads[i];

		// Check if the client sent any message
		if (messageThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			// Temporary values
			auto messageResult = messageThread.get();
			auto messageStatusCode = std::get<0>(messageResult);
			auto messageErrorCode = std::get<1>(messageResult);
			auto messageTimestamp = std::get<2>(messageResult);
			auto messageContent = std::get<3>(messageResult);

			if (messageStatusCode > 0) // Message is received correctly
			{
				// Loop through received message(s)
				for (const auto& character : messageContent)
				{
					if (character == ';') // End of current message
					{
						if (clientUsername.empty()) // Handle username message
						{
							// Check if username does not exist yet
							if (std::find(_clientUsernames.begin(), _clientUsernames.end(), _currentTcpMessageBuild) == _clientUsernames.end())
							{
								// Set new username
								clientUsername = _currentTcpMessageBuild;
								_sendMessageTCP(clientSocketID, "ACCEPTED", true);
								_currentTcpMessageBuild = "";

								// Logging
								Logger::throwInfo("Networking client \"" + clientUsername + "\" connected to the server!");
							}
							else
							{
								// Reject client
								_sendMessageTCP(clientSocketID, "USER_ALREADY_CONNECTED", true);
								_disconnectingClientSocketIDs.push_back(clientSocketID);
								_currentTcpMessageBuild = "";

								// Prevent reading next messages
								break;
							}
						}
						else if (_currentTcpMessageBuild == "PING") // Handle ping message
						{
							auto pingMessage = "PING" + std::to_string(messageTimestamp) + "_" + std::to_string(Tools::getTimeSinceEpochMS());
							_sendMessageTCP(clientSocketID, pingMessage, true);
							_currentTcpMessageBuild = "";
						}
						else // Handle other messages
						{
							_pendingMessages.push_back(NetworkClientMessage(clientIP, clientPort, clientUsername, _currentTcpMessageBuild));
							_currentTcpMessageBuild = "";
						}					}
					else // Add to current message
					{
						_currentTcpMessageBuild += character;
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
				if (messageErrorCode == WSAECONNRESET || messageErrorCode == WSAECONNABORTED) // Client lost socket connection
				{
					_disconnectClient(clientSocketID);
					goto BEGIN;
				}
				else // Something really bad happened
				{
					Logger::throwError("Networking server TCP receive failed with error code: ", messageErrorCode);
				}
			}

			// Spawn new message thread
			messageThread = std::async(std::launch::async, &NetworkServerAPI::_waitForClientMessageTCP, this, clientSocketID);
		}
	}

	// Receive incoming UDP messages
	while (_udpMessageThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
	{
		// Temporary values
		auto messageResult = _udpMessageThread.get();
		auto messageStatusCode = std::get<0>(messageResult);
		auto messageErrorCode = std::get<1>(messageResult);
		auto messageTimestamp = std::get<2>(messageResult);
		auto messageContent = std::get<3>(messageResult);

		if (messageStatusCode > 0) // Message is received correctly
		{
			// Extract username & content
			auto username = messageContent.substr(0, messageContent.find(';'));
			auto content = messageContent.substr(messageContent.find(';') + 1);

			// Try to find client
			for (size_t i = 0; i < _clientUsernames.size(); i++)
			{
				// Check if username matches
				if (username == _clientUsernames[i])
				{
					// Add new message
					_pendingMessages.push_back(NetworkClientMessage(_clientIPs[i], _clientPorts[i], username, content));
				}
			}			
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking server UDP receive failed with error code: ", messageErrorCode);
		}

		// Spawn new message thread
		_udpMessageThread = std::async(std::launch::async, &NetworkServerAPI::_waitForClientMessageUDP, this, _udpMessageSocketID);
	}
}