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
	auto infoResult = getaddrinfo(NULL, SERVER_PORT.c_str(), &hints, &addressInfo);
	if (infoResult != 0)
	{
		Logger::throwError("Network server startup (address info) failed with error code: ", infoResult);
		return;
	}

	// Create socket for listening
	_listenSocketID = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (_listenSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Network server startup (socket create) failed with error code: ", WSAGetLastError());
	}

	// Bind the listening socket
	auto bindResult = bind(_listenSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if (bindResult == SOCKET_ERROR)
	{
		Logger::throwError("Network server startup (socket bind) failed with error code: ", WSAGetLastError());
	}

	// Address info not needed anymore
	freeaddrinfo(addressInfo);

	_isRunning = true;
}

void NetworkServer::stop()
{
	// Error checking
	if (!_isRunning)
	{
		Logger::throwError("Trying to stop network server: not running!");
	}

	//closesocket(_clientSocketID);
	closesocket(_listenSocketID);
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
	
	// Update client connection requests
	if (_listeningThread == nullptr)
	{
		// Listen for any incoming client connection requests
		auto listenResult = listen(_listenSocketID, SOMAXCONN);
		if (listenResult == SOCKET_ERROR)
		{
			Logger::throwError("Network server listen failed with error code: ", WSAGetLastError());
		}

		// Wait for client request in different thread
		_listeningThread = new std::future<SOCKET>(std::async(std::launch::async, &NetworkServer::_waitForClient, this, _listenSocketID));
	}
	else
	{
		// Check if client requested connection
		if (_listeningThread->valid())
		{
			if (_listeningThread->wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
			{
				auto clientSocketID = _listeningThread->get();
				if (clientSocketID == INVALID_SOCKET)
				{
					Logger::throwError("Network server accept failed with error code: ", WSAGetLastError());
				}
				_clientSocketIDs.push_back(clientSocketID);
				delete _listeningThread;
				_listeningThread = nullptr;
				std::cout << "Client connected!" << std::endl;
			}
		}
	}

	// Receive client
	if (!_clientSocketIDs.empty())
	{
		char recvbuf[512];
		int iResult;
		int recvbuflen = 512;
		do {

			iResult = recv(_clientSocketIDs[0], recvbuf, recvbuflen, 0);
			// error 10054
			if (iResult > 0)
			{
				std::cout << recvbuf[0] << std::endl;
			}
			else if (iResult == 0)
			{
				printf("Connection closing...\n");
			}
			else
			{
				Logger::throwError("Network server receive failed with error code: ", WSAGetLastError());
			}

		} while (iResult > 0);
	}
}

bool NetworkServer::isRunning()
{
	return _isRunning;
}

SOCKET NetworkServer::_waitForClient(SOCKET listenSocketID)
{
	return accept(listenSocketID, NULL, NULL);
}