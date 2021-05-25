#define WIN32_LEAN_AND_MEAN

#include "network_server.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkServer::isRunning()
{
	return _isRunning;
}

bool NetworkServer::isRequestPending()
{
	return !_receivedRequestQueue.empty();
}

void NetworkServer::loadNextRequest()
{
	_receivedRequestQueue.erase(_receivedRequestQueue.begin());
}

const NetworkRequest NetworkServer::getPendingRequest()
{
	return _receivedRequestQueue.front();
}

void NetworkServer::_saveClient(SOCKET clientSocketID)
{
	// Extract IP address
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(clientSocketID, (struct sockaddr*)&socketAddress, &socketAddressLength);
	auto ipAddress = string(inet_ntoa(socketAddress.sin_addr));

	// Add client
	_clientSocketIDs.push_back(clientSocketID);
	_clientIPs.push_back(ipAddress);
	_clientRequestThreads.push_back(std::async(std::launch::async, &NetworkServer::_waitForClientRequest, this, clientSocketID));
}

void NetworkServer::_deleteClient(const string& ipAddress)
{
	for (unsigned int i = 0; i < _clientIPs.size(); i++)
	{
		if (_clientIPs[i] == ipAddress)
		{
			closesocket(_clientSocketIDs[i]);
			_clientSocketIDs.erase(_clientSocketIDs.begin() + i);
			_clientIPs.erase(_clientIPs.begin() + i);
			_clientRequestThreads.erase(_clientRequestThreads.begin() + i);
			break;
		}
	}
}

SOCKET NetworkServer::_waitForClientConnection(SOCKET listenSocketID)
{
	return accept(listenSocketID, NULL, NULL);
}

pair<int, string> NetworkServer::_waitForClientRequest(SOCKET clientSocketID)
{
	// Retrieve bytes & size
	char buffer[MAX_REQUEST_BYTES];
	int bufferLength = MAX_REQUEST_BYTES;
	auto statusCode = recv(clientSocketID, buffer, bufferLength, 0);

	if (statusCode > 0) // Request received correctly
	{
		return std::make_pair(statusCode, string(buffer, statusCode));
	}
	else // Something else happened
	{
		return std::make_pair(statusCode, "");
	}
}