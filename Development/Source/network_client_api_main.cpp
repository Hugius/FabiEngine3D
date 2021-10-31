#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkClientAPI::NetworkClientAPI()
	:
	_tcpSocketID(INVALID_SOCKET),
	_udpSocketID(INVALID_SOCKET)
{

}

NetworkClientAPI::~NetworkClientAPI()
{
	if(_isRunning)
	{
		stop();
	}
}

void NetworkClientAPI::start(const string& username)
{
	// Must not be running
	if(_isRunning)
	{
		Logger::throwError("NetworkClientAPI::start::1");
	}

	// Validate username
	if(username.empty())
	{
		Logger::throwError("NetworkClientAPI::start::2");
	}
	if(username.size() > NetworkUtils::MAX_USERNAME_CHARACTERS)
	{
		Logger::throwError("NetworkClientAPI::start::3");
	}
	if(NetworkUtils::isMessageReserved(username))
	{
		Logger::throwError("NetworkClientAPI::start::4");
	}
	if(find(username.begin(), username.end(), ';') != username.end())
	{
		Logger::throwError("NetworkClientAPI::start::5");
	}

	// Client is now operable
	_username = username;
	_isRunning = true;
}

void NetworkClientAPI::connectToServer(const string& serverIP, const string& serverPort)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::connectToServer::1");
	}

	// Must not already be connected
	if(_isConnectedToServer)
	{
		Logger::throwError("NetworkClientAPI::connectToServer::2");
	}

	// Must not already be connecting
	if(_isConnectingToServer)
	{
		Logger::throwError("NetworkClientAPI::connectToServer::3");
	}

	// Must be a valid IP
	if(!isValidServerIP(serverIP))
	{
		Logger::throwError("NetworkClientAPI::connectToServer::4");
	}

	// Save server address
	_serverIP = serverIP;
	_serverPort = serverPort;

	// Load TCP socket
	_setupTCP();

	// Load UDP socket
	_setupUDP();

	// Client is now connecting
	_isConnectingToServer = true;
}

void NetworkClientAPI::disconnectFromServer(bool mustBeAccepted)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::disconnectFromServer");
	}

	// Must be connected & optionally accepted
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		Logger::throwError("NetworkClientAPI::disconnectFromServer");
	}

	// Close connection socket
	if(_tcpSocketID != INVALID_SOCKET)
	{
		closesocket(_tcpSocketID);
	}

	// Close UDP message socket
	if(_udpSocketID != INVALID_SOCKET)
	{
		closesocket(_udpSocketID);
	}

	// Reset variables
	_tcpSocketID = INVALID_SOCKET;
	_udpSocketID = INVALID_SOCKET;
	_pendingMessages.clear();
	_pingLatencies.clear();
	_lastMilliseconds = 0;
	_tcpMessageBuild = "";
	_serverIP = "";
	_serverPort = "";
	_isConnectedToServer = false;
	_isAcceptedByServer = false;
	_isWaitingForPing = false;
	_mustDisconnectFromServer = false;
}

void NetworkClientAPI::stop()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::stop");
	}

	// Close TCP socket
	if(_tcpSocketID != INVALID_SOCKET)
	{
		closesocket(_tcpSocketID);
	}

	// Close UDP socket
	if(_udpSocketID != INVALID_SOCKET)
	{
		closesocket(_udpSocketID);
	}

	// Reset variables
	_tcpSocketID = INVALID_SOCKET;
	_udpSocketID = INVALID_SOCKET;
	_pendingMessages.clear();
	_pingLatencies.clear();
	_lastMilliseconds = 0;
	_username = "";
	_tcpMessageBuild = "";
	_serverIP = "";
	_serverPort = "";
	_isConnectedToServer = false;
	_isConnectingToServer = false;
	_isAcceptedByServer = false;
	_isWaitingForPing = false;
	_mustDisconnectFromServer = false;
	_isRunning = false;
}