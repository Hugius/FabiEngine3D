#define WIN32_LEAN_AND_MEAN

#include "networking_client.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkingClient::NetworkingClient()
	:
	_tcpSocket(INVALID_SOCKET),
	_udpSocket(INVALID_SOCKET)
{

}

NetworkingClient::~NetworkingClient()
{
	if(_isRunning)
	{
		stop();
	}
}

void NetworkingClient::start(const string& username)
{
	// Must not be running
	if(_isRunning)
	{
		Logger::throwError("NetworkingClient::start::1");
	}

	// Validate username
	if(username.empty())
	{
		Logger::throwError("NetworkingClient::start::2");
	}
	if(username.size() > NetworkingUtils::MAX_USERNAME_CHARACTERS)
	{
		Logger::throwError("NetworkingClient::start::3");
	}
	if(NetworkingUtils::isMessageReserved(username))
	{
		Logger::throwError("NetworkingClient::start::4");
	}
	if(find(username.begin(), username.end(), ';') != username.end())
	{
		Logger::throwError("NetworkingClient::start::5");
	}

	// Client is now operable
	_username = username;
	_isRunning = true;
}

void NetworkingClient::connectToServer(const string& serverIP, const string& serverPort)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingClient::connectToServer::1");
	}

	// Must not already be connected
	if(_isConnectedToServer)
	{
		Logger::throwError("NetworkingClient::connectToServer::2");
	}

	// Must not already be connecting
	if(_isConnectingToServer)
	{
		Logger::throwError("NetworkingClient::connectToServer::3");
	}

	// Must be a valid IP
	if(!isValidServerIP(serverIP))
	{
		Logger::throwError("NetworkingClient::connectToServer::4");
	}

	// Save server address
	_serverIP = serverIP;
	_serverPort = serverPort;

	// Load TCP socket
	_setupTcp();

	// Load UDP socket
	_setupUdp();

	// Client is now connecting
	_isConnectingToServer = true;
}

void NetworkingClient::disconnectFromServer(bool mustBeAccepted)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingClient::disconnectFromServer");
	}

	// Must be connected & optionally accepted
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		Logger::throwError("NetworkingClient::disconnectFromServer");
	}

	// Close connection socket
	if(_tcpSocket != INVALID_SOCKET)
	{
		closesocket(_tcpSocket);
	}

	// Close UDP message socket
	if(_udpSocket != INVALID_SOCKET)
	{
		closesocket(_udpSocket);
	}

	// Reset variables
	_tcpSocket = INVALID_SOCKET;
	_udpSocket = INVALID_SOCKET;
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

void NetworkingClient::stop()
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingClient::stop");
	}

	// Close TCP socket
	if(_tcpSocket != INVALID_SOCKET)
	{
		closesocket(_tcpSocket);
	}

	// Close UDP socket
	if(_udpSocket != INVALID_SOCKET)
	{
		closesocket(_udpSocket);
	}

	// Reset variables
	_tcpSocket = INVALID_SOCKET;
	_udpSocket = INVALID_SOCKET;
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