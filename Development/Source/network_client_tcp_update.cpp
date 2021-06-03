#define WIN32_LEAN_AND_MEAN

#include "network_client_tcp.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

void NetworkClientTCP::update()
{
	// Must be running first
	if (!_isRunning)
	{
		return;
	}

	// Clear all received messages from last frame
	_pendingMessages.clear();

	// Handle server connection
	if (_isConnectingToServer)
	{
		// Check if connection thread is finished
		if (_connectionThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			// Retrieve error code
			auto errorCode = _connectionThread.get();

			if (errorCode == 0) // Successfully connected with server
			{
				// Not connecting anymore
				_isConnectingToServer = false;
				_isConnectedToServer = true;

				// Send username to server
				if (!_sendMessage(_username, false))
				{
					return;
				}

				// Start a thread to listen for server messages
				_serverMessageThread = std::async(std::launch::async, &NetworkClientTCP::_waitForServerMessage, this, _serverSocketID);
			}
			else if (errorCode == WSAECONNREFUSED) // Cannot connect with server
			{
				_isConnectingToServer = false;
			}
			else // Something really bad happened
			{
				Logger::throwError("Networking client connect failed with error code: ", errorCode);
			}
		}
		else
		{
			return; // Wait until client is connected to server
		}
	}

	// Must be connected first
	if (!_isConnectedToServer)
	{
		return;
	}

	// Update server ping
	if (!_isWaitingForPing)
	{
		// Send ping & validate
		if (!_sendMessage("PING", true))
		{
			return;
		}

		// Start measuring time
		_isWaitingForPing = true;
		_lastMilliseconds = Tools::getTimeSinceEpochMS();
	}

	// Check if the server sent any messages
	if (_serverMessageThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
	{
		// Temporary values
		auto messageResult = _serverMessageThread.get();
		auto messageErrorCode = std::get<0>(messageResult);
		auto messageStatusCode = std::get<1>(messageResult);
		auto messageTimestamp = std::get<2>(messageResult);
		auto messageContent = std::get<3>(messageResult);

		if (messageStatusCode > 0) // Message is received correctly
		{
			// Loop through received message(s)
			for (const auto& character : messageContent)
			{
				if (character == ';') // End of current message
				{
					if (_currentMessageBuild == "ACCEPTED") // Handle accept message
					{
						_isAcceptedByServer = true;
						_currentMessageBuild = "";
					}
					else if (_currentMessageBuild == "PING") // Handle ping message
					{
						auto currentTimeMS = Tools::getTimeSinceEpochMS();
						_serverPing = (currentTimeMS - _lastMilliseconds);
						_isWaitingForPing = false;
						_currentMessageBuild = "";
					}
					else // Handle other messages
					{
						_pendingMessages.push_back(NetworkServerMessage(_currentMessageBuild));
						_currentMessageBuild = "";
					}
				}
				else // Add to current message
				{
					_currentMessageBuild += character;
				}
			}
		}
		else if (messageStatusCode == 0) // Server closed socket connection
		{
			disconnectFromServer();
			return;
		}
		else // Receive failed
		{
			if (messageErrorCode == WSAECONNRESET || messageErrorCode == WSAECONNABORTED) // Server lost socket connection
			{
				disconnectFromServer();
				return;
			}
			else // Something really bad happened
			{
				Logger::throwError("Networking server receive failed with error code: ", messageErrorCode);
			}
		}

		// Spawn new message thread
		_serverMessageThread = std::async(std::launch::async, &NetworkClientTCP::_waitForServerMessage, this, _serverSocketID);
	}
}