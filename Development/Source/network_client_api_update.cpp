#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

void NetworkClientAPI::update()
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
				if (!_sendMessageTCP(_username, false))
				{
					return;
				}

				// Start a thread to listen for server messages
				_serverMessageThreadTCP = std::async(std::launch::async, &NetworkClientAPI::_waitForServerMessageTCP, this, _tcpServerSocketID);
				_serverMessageThreadUDP = std::async(std::launch::async, &NetworkClientAPI::_waitForServerMessageUDP, this, _udpServerSocketID);
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
		if (!_sendMessageTCP("PING", true))
		{
			return;
		}

		// Start measuring time
		_isWaitingForPing = true;
		_lastMilliseconds = Tools::getTimeSinceEpochMS();
	}

	// Check if the server sent any TCP messages
	if (_serverMessageThreadTCP.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
	{
		// Temporary values
		auto messageResult = _serverMessageThreadTCP.get();
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
					if (_currentTcpMessageBuild == "ACCEPTED") // Handle accept message
					{
						_isAcceptedByServer = true;
						_currentTcpMessageBuild = "";
					}
					else if (_currentTcpMessageBuild.substr(0, 4) == "PING") // Handle ping message
					{
						// Calculate server ping
						auto pingData = _currentTcpMessageBuild.substr(4);
						auto serverReceiveEpoch = stoll(pingData.substr(0, pingData.find('_')));
						auto serverSendEpoch = stoll(pingData.substr(pingData.find('_') + 1));
						auto forthPing = (serverReceiveEpoch - _lastMilliseconds);
						auto backPing = (Tools::getTimeSinceEpochMS() - serverSendEpoch);

						// Register server ping
						if (_serverPings.size() == 10)
						{
							_serverPings.clear();
						}
						_serverPings.push_back(static_cast<unsigned int>(forthPing + backPing));
						_isWaitingForPing = false;
						_currentTcpMessageBuild = "";
					}
					else // Handle other messages
					{
						_pendingMessages.push_back(NetworkServerMessage(_currentTcpMessageBuild));
						_currentTcpMessageBuild = "";
					}
				}
				else // Add to current message
				{
					_currentTcpMessageBuild += character;
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
				Logger::throwError("Networking server TCP receive failed with error code: ", messageErrorCode);
			}
		}

		// Spawn new message thread
		_serverMessageThreadTCP = std::async(std::launch::async, &NetworkClientAPI::_waitForServerMessageTCP, this, _tcpServerSocketID);
	}
}