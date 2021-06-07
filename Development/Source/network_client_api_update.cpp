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
				if (!_sendTcpMessage(_username, false))
				{
					return;
				}

				// Start a thread to wait for TCP messages
				_tcpMessageThread = std::async(std::launch::async, &NetworkClientAPI::_waitForTcpMessage, this, _connectionSocketID);
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

	// Must be connected
	if (!_isConnectedToServer)
	{
		return;
	}

	// Update server pinging
	if (_isAcceptedByServer && !_isWaitingForPing)
	{
		// Send ping
		if (!_sendTcpMessage("PING", true))
		{
			return;
		}

		// Start measuring latency
		_isWaitingForPing = true;
		_lastMilliseconds = Tools::getTimeSinceEpochMS();
	}

	// Receive incoming TCP messages
	if (_tcpMessageThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
	{
		// Temporary values
		const auto& messageResult = _tcpMessageThread.get();
		const auto& messageStatusCode = std::get<0>(messageResult);
		const auto& messageErrorCode = std::get<1>(messageResult);
		const auto& messageTimestamp = std::get<2>(messageResult);
		const auto& messageContent = std::get<3>(messageResult);

		if (messageStatusCode > 0) // Message is received correctly
		{
			// Loop through received message(s)
			for (const auto& character : messageContent)
			{
				if (character == ';') // End of current message
				{
					if (_currentTcpMessageBuild.substr(0, 8) == "ACCEPTED") // Handle accept message
					{
						auto tcpPort = _currentTcpMessageBuild.substr(8);
						_setupUDP(tcpPort); // UDP uses the same port as TCP
						_isAcceptedByServer = true;
						_currentTcpMessageBuild = "";
					}
					else if (_currentTcpMessageBuild.substr(0, 4) == "PING") // Handle ping message
					{
						// Calculate server latency
						auto pingData = _currentTcpMessageBuild.substr(4);
						auto serverReceiveEpoch = stoll(pingData.substr(0, pingData.find('_')));
						auto serverSendEpoch = stoll(pingData.substr(pingData.find('_') + 1));
						auto forthPing = (serverReceiveEpoch - _lastMilliseconds);
						auto backPing = (Tools::getTimeSinceEpochMS() - serverSendEpoch);

						// Register server latency
						if (_pingLatencies.size() == 10)
						{
							_pingLatencies.clear();
						}
						_pingLatencies.push_back(static_cast<unsigned int>(forthPing + backPing));
						_isWaitingForPing = false;
						_currentTcpMessageBuild = "";
					}
					else // Handle other messages
					{
						_pendingMessages.push_back(NetworkServerMessage(_currentTcpMessageBuild));
						_currentTcpMessageBuild = "";
					}
				}
				else // Add to current message build
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

		// Spawn new TCP message thread
		_tcpMessageThread = std::async(std::launch::async, &NetworkClientAPI::_waitForTcpMessage, this, _connectionSocketID);
	}

	// Receive incoming UDP messages
	while (NetworkUtils::isMessageReady(_udpMessageSocketID))
	{
		// Message data
		const auto& messageResult = _receiveUdpMessage(_udpMessageSocketID);
		const auto& messageStatusCode = std::get<0>(messageResult);
		const auto& messageErrorCode = std::get<1>(messageResult);
		const auto& messageTimestamp = std::get<2>(messageResult);
		const auto& messageContent = std::get<3>(messageResult);
		const auto& messageIP = std::get<4>(messageResult);
		const auto& messagePort = std::get<5>(messageResult);

		if (messageStatusCode > 0) // Message is received correctly
		{
			if ((messageIP == _serverIP) && (messagePort == _serverPort)) // Message must come from server
			{
				_pendingMessages.push_back(NetworkServerMessage(messageContent));
			}
		}
		else if ((messageStatusCode == 0) || (messageErrorCode == WSAECONNRESET) || (messageErrorCode == WSAECONNABORTED))
		{
			// Wrong packet, do nothing
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking server UDP receive failed with error code: ", messageErrorCode);
		}
	}
}