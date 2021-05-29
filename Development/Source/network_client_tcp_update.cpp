#define WIN32_LEAN_AND_MEAN

#include "network_client_tcp.hpp"
#include "logger.hpp"

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
	if (!_isConnectedToServer)
	{
		if (_connectionThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			// Temporary values
			auto errorCode = _connectionThread.get();

			if (errorCode == 0) // Successfully connected with server
			{
				_isConnectedToServer = true;
				_serverMessageThread = std::async(std::launch::async, &NetworkClientTCP::_waitForServerMessage, this, _serverSocketID);
			}
			else if (errorCode == WSAECONNREFUSED) // Cannot connect with server
			{
				// Spawn thread again for another attempt
				_connectionThread = std::async(std::launch::async, &NetworkClientTCP::_connectWithServer, this, _serverSocketID, _addressInfo);
			}
			else // Something really bad happened
			{
				Logger::throwError("Networking client connect failed with error code: ", errorCode);
			}
		}

		return;
	}

	// Check if the client sent any message
	if (_serverMessageThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
	{
		// Temporary values
		auto messageResult = _serverMessageThread.get();
		auto messageStatusCode = std::get<0>(messageResult);
		auto messageContent = std::get<1>(messageResult);
		auto messageErrorCode = std::get<2>(messageResult);
		//messageContent = messageContent.substr(0, messageContent.find(']') + 1); <---

		if (messageStatusCode > 0) // Message is received correctly
		{
			// Extract IP address & port
			auto serverIP = NetworkUtils::extractIP(_serverSocketID);
			auto serverPort = NetworkUtils::extractPort(_serverSocketID);

			// Add message
			_pendingMessages.push_back(NetworkMessage(serverIP, serverPort, messageContent));
		}
		else if (messageStatusCode == 0) // Server closed socket connection
		{
			_closeConnection();
			_initiateConnection();
		}
		else // Receive failed
		{
			if (messageErrorCode == WSAECONNRESET) // Server lost socket connection
			{
				_closeConnection();
				_initiateConnection();
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