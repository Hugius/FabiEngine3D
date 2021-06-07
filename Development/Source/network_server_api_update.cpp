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
			if (!_sendTcpMessage(clientSocketID, "SERVER_FULL", true))
			{
				return;
			}
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
		// Client data
		const auto& clientSocketID = _clientSocketIDs[i];
		const auto& clientIP = _clientIPs[i];
		const auto& clientPort = _clientPorts[i];
		auto& clientUsername = _clientUsernames[i];
		auto& clientMessageBuild = _clientMessageBuilds[i];
		auto& messageThread = _tcpMessageThreads[i];

		// Check if the client sent any message
		if (messageThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			// Message data
			const auto& messageResult = messageThread.get();
			const auto& messageStatusCode = std::get<0>(messageResult);
			const auto& messageErrorCode = std::get<1>(messageResult);
			const auto& messageTimestamp = std::get<2>(messageResult);
			const auto& messageContent = std::get<3>(messageResult);

			if (messageStatusCode > 0) // Message is received correctly
			{
				for (const auto& character : messageContent) // Loop through received messages
				{
					if (character == ';') // End of current message
					{
						if (clientUsername.empty()) // Handle username message
						{
							// Check if username does not exist yet
							if (std::find(_clientUsernames.begin(), _clientUsernames.end(), clientMessageBuild) == _clientUsernames.end())
							{
								// Save new username
								clientUsername = clientMessageBuild;
								if (!_sendTcpMessage(clientSocketID, "ACCEPTED" + clientPort, true))
								{
									return;
								}
								clientMessageBuild = "";

								// Logging
								Logger::throwInfo("Networking client \"" + clientUsername + "\" connected to the server!");
							}
							else
							{
								// Reject client
								if (!_sendTcpMessage(clientSocketID, "USER_ALREADY_CONNECTED", true))
								{
									return;
								}
								_disconnectingClientSocketIDs.push_back(clientSocketID);
								clientMessageBuild = "";

								// Prevent reading next messages
								break;
							}
						}
						else if (clientMessageBuild == "PING") // Handle ping message
						{
							// Compose ping message
							auto pingMessage = 
								"PING" + 
								std::to_string(messageTimestamp) + "_" + // Timestamp of receive
								std::to_string(Tools::getTimeSinceEpochMS()); // Timestamp of send

							// Send ping message
							if (!_sendTcpMessage(clientSocketID, pingMessage, true))
							{
								return;
							}
							clientMessageBuild = "";
						}
						else // Handle other messages
						{
							_pendingMessages.push_back(NetworkClientMessage(clientIP, clientPort, clientUsername, clientMessageBuild));
							clientMessageBuild = "";
						}					
					}
					else // Add to current message build
					{
						clientMessageBuild += character;
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
			messageThread = std::async(std::launch::async, &NetworkServerAPI::_waitForTcpMessage, this, clientSocketID);
		}
	}
	
	// Receive incoming UDP messages
	fd_set socketSet;
	timeval timeInterval = { 0 , 1 }; // 1 microsecond
	FD_ZERO(&socketSet);
	FD_SET(_udpMessageSocketID, &socketSet);
	while (select(0, &socketSet, nullptr, nullptr, &timeInterval) > 0) // Check if a UDP message is ready to receive
	{
		// Message data
		auto messageResult = _receiveUdpMessage(_udpMessageSocketID);
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
					break;
				}
			}
		}
		else if (messageStatusCode == 0 || messageErrorCode == WSAECONNRESET || messageErrorCode == WSAECONNABORTED)
		{
			// Wrong packet, do nothing
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking server UDP receive failed with error code: ", messageErrorCode);
		}
	}
}