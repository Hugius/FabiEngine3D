#define WIN32_LEAN_AND_MEAN

#include "network_server.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

void NetworkServer::start()
{
	// Error checking
	if (_isRunning)
	{
		Logger::throwError("Trying to start network server: already running!");
	}

	// Compose address info hints
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // Ipv4 address
	hints.ai_socktype = SOCK_STREAM; // Streaming socket
	hints.ai_protocol = IPPROTO_TCP; // TCP protocol
	hints.ai_flags = AI_PASSIVE; // Required flag

	// Create address info
	struct addrinfo* addressInfo = NULL;
	auto infoStatusCode = getaddrinfo(NULL, SERVER_PORT.c_str(), &hints, &addressInfo);
	if (infoStatusCode != 0)
	{
		Logger::throwError("Network server startup (address info) failed with error code: ", infoStatusCode);
		return;
	}

	// Create socket for listening
	_listenSocketID = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (_listenSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Network server startup (socket create) failed with error code: ", WSAGetLastError());
	}

	// Bind the listening socket
	auto bindStatusCode = bind(_listenSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if (bindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Network server startup (socket bind) failed with error code: ", WSAGetLastError());
	}

	// Address info not needed anymore
	freeaddrinfo(addressInfo);

	// Enable listening for any client connection requests
	auto listenStatusCode = listen(_listenSocketID, SOMAXCONN);
	if (listenStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Network server startup (socket listen) failed with error code: ", WSAGetLastError());
	}

	// Spawn an initial thread for accepting incoming connection requests
	_connectionThread = std::async(std::launch::async, &NetworkServer::_waitForClientConnection, this, _listenSocketID);

	_isRunning = true;
}

void NetworkServer::stop()
{
	// Error checking
	if (!_isRunning)
	{
		Logger::throwError("Trying to stop network server: not running!");
	}

	// Close all network sockets
	closesocket(_listenSocketID);
	for (auto& socketID : _clientSocketIDs)
	{
		closesocket(socketID);
	}

	// Miscellaneous
	WSACleanup();
	_isRunning = false;
}

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
		sockaddr_in socketAddress;
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

bool NetworkServer::isRunning()
{
	return _isRunning;
}

SOCKET NetworkServer::_waitForClientConnection(SOCKET listenSocketID)
{
	return accept(listenSocketID, NULL, NULL);
}

pair<int, string> NetworkServer::_waitForClientMessage(SOCKET clientSocketID)
{
	char buffer[3];
	int bufferLength = 3;

	auto statusCode = recv(clientSocketID, buffer, bufferLength, 0);

	return std::make_pair(statusCode, string(buffer));
}