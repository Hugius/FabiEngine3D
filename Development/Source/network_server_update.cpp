#define WIN32_LEAN_AND_MEAN

#include "network_server.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

void NetworkServer::update()
{
	// Must be running first
	if (!_isRunning)
	{
		return;
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
		if (_clientIPs.size() == MAX_CLIENT_COUNT)
		{
			_sendMessageToClient(clientSocketID, "SERVER_FULL");
			closesocket(clientSocketID);
		}
		else
		{
			// Save new client
			_acceptClient(clientSocketID);

			// Logging
			Logger::throwInfo("Networking client with IP \"" + _clientIPs.back() + "\" connected to the server!");
		}

		// Spawn connection thread again for next client
		_spawnConnectionThread();
	}

	// Receive incoming client messages
BEGIN:
	for (size_t i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Temporary values
		auto clientSocketID = _clientSocketIDs[i];
		auto ipAddress = _clientIPs[i];
		auto& messageThread = _clientMessageThreads[i];

		// Check if the client sent any message
		if (messageThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			// Temporary values
			auto messageResult = messageThread.get();
			auto messageStatusCode = std::get<0>(messageResult);
			auto messageContent = std::get<1>(messageResult);
			auto messageErrorCode = std::get<2>(messageResult);

			if (messageStatusCode > 0) // Message is received correctly
			{
				_receivedMessageQueue.push_back(make_shared<NetworkMessage>(ipAddress, messageContent));
			}
			else if (messageStatusCode == 0) // Client closed socket connection
			{
				Logger::throwInfo("Networking client with IP \"" + ipAddress + "\" disconnected from the server!");
				_disconnectClient(ipAddress);
				goto BEGIN;
			}
			else // Receive failed
			{
				if (messageErrorCode == WSAECONNRESET) // Client lost socket connection
				{
					Logger::throwInfo("Networking client with IP \"" + ipAddress + "\" lost connection with the server!");
					_disconnectClient(ipAddress);
					goto BEGIN;
				}
				else // Something really bad happened
				{
					Logger::throwError("Networking server receive failed with error code: ", messageErrorCode);
				}
			}

			// Spawn new message thread
			messageThread = std::async(std::launch::async, &NetworkServer::_waitForClientMessage, this, clientSocketID);
		}
	}
}