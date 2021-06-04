#define WIN32_LEAN_AND_MEAN

#include "network_client_udp.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkClientUDP::NetworkClientUDP() :
	_serverSocketID(INVALID_SOCKET)
{

}

NetworkClientUDP::~NetworkClientUDP()
{
	if (_isRunning)
	{
		stop();
	}
}

void NetworkClientUDP::start(const string& username)
{
	// Must not be running
	if (_isRunning)
	{
		Logger::throwWarning("UDP networking client tried to start: already running!");
		return;
	}

	// Validate username
	if (username.empty())
	{
		Logger::throwWarning("UDP networking client tried to start: empty username!");
		return;
	}
	else if (NetworkUtils::isMessageReserved(username))
	{
		Logger::throwWarning("UDP networking client tried to start: username is reserved!");
		return;
	}
	else
	{
		_username = username;
	}

	// Client is now operable
	_isRunning = true;
}

void NetworkClientUDP::stop()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("UDP networking client tried to stop: not running!");
		return;
	}

	// Reset variables
	_username = "";
	_isRunning = false;
}