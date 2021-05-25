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

		// Extract IP address
		sockaddr_in socketAddress = sockaddr_in();
		int socketAddressLength = sizeof(socketAddress);
		auto peerResult = getpeername(clientSocketID, (struct sockaddr*) &socketAddress, &socketAddressLength);
		auto ipAddress = string(inet_ntoa(socketAddress.sin_addr));

		// Add client
		_clientSocketIDs.push_back(clientSocketID);
		_clientIPs.push_back(ipAddress);
		_clientMessageThreads.push_back(std::async(std::launch::async, &NetworkServer::_waitForClientMessage, this, clientSocketID));

		// Spawn thread again
		_connectionThread = std::async(std::launch::async, &NetworkServer::_waitForClientConnection, this, _listenSocketID);

		// Logging
		Logger::throwInfo("A network client with IP \"" + ipAddress + "\" connected to the server!");
	}

	// Update client message receiving
	for (unsigned int i = 0; i < _clientSocketIDs.size(); i++)
	{
		auto clientSocketID = _clientSocketIDs[i];
		auto& messageThread = _clientMessageThreads[i];

		// Check if the client sent any message
		if (messageThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			auto messageResult = messageThread.get();
			auto messageStatusCode = messageResult.first;
			auto messageString = messageResult.second;

			if (messageStatusCode > 0)
			{
				std::cout << messageString << " " << messageString.size() << std::endl;
			}
			else if (messageStatusCode == 0)
			{
				// closed
			}
			else if (messageStatusCode == 10054)
			{
				// forcibly closed
			}
			else
			{
				Logger::throwError("Network server receive failed with error code: ", WSAGetLastError());
			}

			messageThread = std::async(std::launch::async, &NetworkServer::_waitForClientMessage, this, clientSocketID);
		}
	}
}