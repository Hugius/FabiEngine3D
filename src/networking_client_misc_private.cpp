#define WIN32_LEAN_AND_MEAN

#include "networking_client.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::launch;

bool NetworkingClient::_sendTcpMessage(const string& content, bool isReserved, bool mustBeAccepted)
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::1");
	}

	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::2");
	}

	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::3");
	}
	if(NetworkingUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::4");
	}
	if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::5");
	}

	string message = (content + ';');

	auto sendStatusCode = send(_tcpSocket, message.c_str(), static_cast<int>(message.size()), 0);

	if(sendStatusCode == SOCKET_ERROR)
	{
		if((WSAGetLastError() == WSAECONNRESET) || (WSAGetLastError() == WSAECONNABORTED))
		{
			disconnectFromServer(mustBeAccepted);
			return false;
		}
		else if(WSAGetLastError() == WSAENOBUFS)
		{
			Logger::throwWarning("Networking client is sending too many TCP messages!");
		}
		else
		{
			Logger::throwError("NetworkingClient::_sendTcpMessage::6 ---> ", WSAGetLastError());
		}
	}

	return true;
}

bool NetworkingClient::_sendUdpMessage(const string& content, bool isReserved, bool mustBeAccepted) const
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::1");
	}

	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::2");
	}

	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::3");
	}
	else if(NetworkingUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::4");
	}
	else if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::5");
	}

	auto socketAddress = NetworkingUtils::composeSocketAddress(_serverIP, _serverPort);

	string message = (_username + ';' + content);

	auto sendStatusCode = sendto(
		_udpSocket,
		message.c_str(),
		static_cast<int>(message.size()),
		0,
		reinterpret_cast<sockaddr*>(&socketAddress),
		sizeof(socketAddress));

	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAENOBUFS)
		{
			Logger::throwWarning("Networking client is sending too many UDP messages!");
		}
		else
		{
			Logger::throwError("NetworkingClient::_sendUdpMessage::6 ---> ", WSAGetLastError());
		}
	}

	return true;
}

int NetworkingClient::_waitForServerConnection(SOCKET socket, const string& serverIP, const string& serverPort) const
{
	auto socketAddress = NetworkingUtils::composeSocketAddress(serverIP, serverPort);

	auto connectStatusCode = connect(
		socket,
		reinterpret_cast<sockaddr*>(&socketAddress),
		sizeof(socketAddress));

	if(connectStatusCode == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}
	else
	{
		return 0;
	}
}

void NetworkingClient::_setupTcp()
{
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	addrinfo* addressInfo = nullptr;
	auto tcpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);
	if(tcpInfoStatusCode != 0)
	{
		Logger::throwError("NetworkingClient::_setupTCP::1 ---> ", tcpInfoStatusCode);
		return;
	}

	_tcpSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_tcpSocket == INVALID_SOCKET)
	{
		Logger::throwError("NetworkingClient::_setupTCP::2 ---> ", WSAGetLastError());
	}

	auto tcpBindStatusCode = bind(_tcpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(tcpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("NetworkingClient::_setupTCP::3 ---> ", WSAGetLastError());
	}

	_connectionThread = async(launch::async, &NetworkingClient::_waitForServerConnection, this, _tcpSocket, _serverIP, _serverPort);
}

void NetworkingClient::_setupUdp()
{
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	addrinfo* addressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);
	if(udpInfoStatusCode != 0)
	{
		Logger::throwError("NetworkingClient::_setupUDP::1 ---> ", udpInfoStatusCode);
		return;
	}

	_udpSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_udpSocket == INVALID_SOCKET)
	{
		Logger::throwError("NetworkingClient::_setupUDP::2 ----> ", WSAGetLastError());
	}

	auto udpBindStatusCode = bind(_udpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(udpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("NetworkingClient::_setupUDP::3 ---> ", WSAGetLastError());
	}

	freeaddrinfo(addressInfo);
}

tuple<int, int, long long, string> NetworkingClient::_waitForTcpMessage(SOCKET socket) const
{
	char buffer[NetworkingUtils::TCP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkingUtils::TCP_BUFFER_BYTES);
	auto receiveResult = recv(socket, buffer, bufferLength, 0);

	if(receiveResult > 0)
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), string(buffer, receiveResult));
	}
	else
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, string, string, string> NetworkingClient::_receiveUdpMessage(SOCKET socket) const
{
	char buffer[NetworkingUtils::UDP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkingUtils::UDP_BUFFER_BYTES);
	sockaddr_in sourceAddress = sockaddr_in();
	int sourceAddressLength = sizeof(sourceAddress);

	auto receiveResult = recvfrom(socket, buffer, bufferLength, 0, reinterpret_cast<sockaddr*>(&sourceAddress), &sourceAddressLength);

	auto IP = NetworkingUtils::extractAddressIP(&sourceAddress);
	auto port = NetworkingUtils::extractAddressPort(&sourceAddress);

	if(receiveResult > 0)
	{
		return make_tuple(receiveResult, WSAGetLastError(), string(buffer, receiveResult), IP, port);
	}
	else
	{
		return make_tuple(receiveResult, WSAGetLastError(), "", IP, port);
	}
}