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

	// Update client connection requesting
	if (_connectionThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
	{
		// Retrieve new client socket ID
		auto clientSocketID = _connectionThread.get();
		if (clientSocketID == INVALID_SOCKET)
		{
			Logger::throwError("Network server accept failed with error code: ", WSAGetLastError());
		}

		// Save new client
		_saveClient(clientSocketID);

		// Spawn connection thread again
		_connectionThread = std::async(std::launch::async, &NetworkServer::_waitForClientConnection, this, _listenSocketID);

		// Logging
		Logger::throwInfo("Network client with IP \"" + _clientIPs.back() + "\" connected to the server!");
	}

	// Update client request receiving
BEGIN:
	for (unsigned int i = 0; i < _clientSocketIDs.size(); i++)
	{
		// Temporary values
		auto clientSocketID = _clientSocketIDs[i];
		auto ipAddress = _clientIPs[i];
		auto& requestThread = _clientRequestThreads[i];

		// Check if the client sent any request
		if (requestThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			// Temporary values
			auto requestResult = requestThread.get();
			auto requestStatusCode = requestResult.first;
			auto requestMessage = requestResult.second;

			if (requestStatusCode > 0) // Request is received correctly
			{
				_receivedRequestQueue.push_back(NetworkRequest(ipAddress, requestMessage));
			}
			else if (requestStatusCode == 0) // Client closed socket connection
			{
				Logger::throwInfo("Network client with IP \"" + ipAddress + "\" disconnected from the server!");
				_deleteClient(ipAddress);
				goto BEGIN;
			}
			else // Receive failed
			{
				if (WSAGetLastError() == 10054) // Client lost socket connection
				{
					Logger::throwInfo("Network client with IP \"" + ipAddress + "\" lost connection with the server!");
					_deleteClient(ipAddress);
					goto BEGIN;
				}
				else
				{
					Logger::throwError("Network server receive failed with error code: ", WSAGetLastError());
				}
			}

			// Spawn new request thread
			requestThread = std::async(std::launch::async, &NetworkServer::_waitForClientRequest, this, clientSocketID);
		}
	}
}