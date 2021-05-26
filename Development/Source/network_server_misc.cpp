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
	return !_requestQueue.empty();
}

void NetworkServer::loadNextRequest()
{
	_requestQueue.erase(_requestQueue.begin());
}

const shared_ptr<NetworkRequest> NetworkServer::getPendingRequest()
{
	return _requestQueue.front();
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

tuple<int, string, int> NetworkServer::_waitForClientRequest(SOCKET clientSocketID)
{
	// Retrieve bytes & size
	char buffer[MAX_REQUEST_BYTES];
	int bufferLength = MAX_REQUEST_BYTES;
	auto receiveResult = recv(clientSocketID, buffer, bufferLength, 0);

	if (receiveResult > 0) // Request received correctly
	{
		return make_tuple(receiveResult, string(buffer, receiveResult), WSAGetLastError());
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, "", WSAGetLastError());
	}
}