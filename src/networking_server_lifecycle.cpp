#define WIN32_LEAN_AND_MEAN

#include "networking_server.hpp"
#include "logger.hpp"

#include <ws2tcpip.h>

using std::launch;

void NetworkingServer::initialize()
{
	_tcpSocket = INVALID_SOCKET;
	_udpSocket = INVALID_SOCKET;
}

void NetworkingServer::cleanup()
{
	if(_isRunning)
	{
		stop();
	}
}

void NetworkingServer::start(int maxClientCount)
{
	if(_isRunning)
	{
		abort();
	}

	if(maxClientCount <= 0)
	{
		abort();
	}

	if(!_setupTcp())
	{
		return;
	}

	if(!_setupUdp())
	{
		return;
	}

	_connectionThread = async(launch::async, &NetworkingServer::_waitForClientConnection, this, _tcpSocket);
	_maxClientCount = maxClientCount;
	_isRunning = true;

	Logger::throwInfo("Started networking server");
}

void NetworkingServer::stop()
{
	if(!_isRunning)
	{
		abort();
	}

	closesocket(_tcpSocket);
	closesocket(_udpSocket);

	while(!_clientSockets.empty())
	{
		_disconnectClient(_clientSockets.back());
	}

	_pendingMessages.clear();
	_tcpSocket = INVALID_SOCKET;
	_udpSocket = INVALID_SOCKET;
	_maxClientCount = 0;
	_newClientIp = "";
	_newClientUsername = "";
	_isRunning = false;

	Logger::throwInfo("Stopped networking server");
}