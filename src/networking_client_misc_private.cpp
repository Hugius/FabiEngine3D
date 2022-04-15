#include "networking_client.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <ws2tcpip.h>

using std::to_string;

const bool NetworkingClient::_sendTcpMessageToServer(const string & content, bool isReserved, bool mustBeAccepted)
{
	if(!_isRunning)
	{
		abort();
	}
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		abort();
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}
	if(NetworkingHelper::_isMessageReserved(content) && !isReserved)
	{
		abort();
	}
	if(content.size() > NetworkingHelper::MAX_MESSAGE_SIZE)
	{
		abort();
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
			Logger::throwInfo("Networking client is sending too many TCP messages");
		}
		else
		{
			Logger::throwDebug(WSAGetLastError());
			abort();
		}
	}

	return true;
}

const bool NetworkingClient::_sendUdpMessageToServer(const string & content, bool isReserved, bool mustBeAccepted) const
{
	if(!_isRunning)
	{
		abort();
	}
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		abort();
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}
	if(NetworkingHelper::_isMessageReserved(content) && !isReserved)
	{
		abort();
	}
	if(content.size() > NetworkingHelper::MAX_MESSAGE_SIZE)
	{
		abort();
	}

	auto socketAddress = NetworkingHelper::_composeSocketAddress(_serverIp, NetworkingHelper::SERVER_PORT);

	string message = (_username + ';' + content);

	auto sendStatusCode = sendto(_udpSocket, message.c_str(), static_cast<int>(message.size()), 0, reinterpret_cast<sockaddr *>(&socketAddress), sizeof(socketAddress));

	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAENOBUFS)
		{
			Logger::throwInfo("Networking client is sending too many UDP messages");
		}
		else
		{
			Logger::throwDebug(WSAGetLastError());
			abort();
		}
	}

	return true;
}

const int NetworkingClient::_waitForServerConnection(SOCKET socket, const string & ip) const
{
	auto socketAddress = NetworkingHelper::_composeSocketAddress(ip, NetworkingHelper::SERVER_PORT);

	auto connectStatusCode = connect(socket, reinterpret_cast<sockaddr *>(&socketAddress), sizeof(socketAddress));

	if(connectStatusCode == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}
	else
	{
		return 0;
	}
}

const bool NetworkingClient::_setupTcp()
{
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	addrinfo * addressInfo = nullptr;
	auto tcpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);
	if(tcpInfoStatusCode != 0)
	{
		Logger::throwDebug(tcpInfoStatusCode);
		abort();
	}

	_tcpSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_tcpSocket == INVALID_SOCKET)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	auto tcpBindStatusCode = bind(_tcpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(tcpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	freeaddrinfo(addressInfo);

	return true;
}

const bool NetworkingClient::_setupUdp()
{
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	addrinfo * addressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);
	if(udpInfoStatusCode != 0)
	{
		Logger::throwDebug(udpInfoStatusCode);
		abort();
	}

	_udpSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_udpSocket == INVALID_SOCKET)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	auto udpBindStatusCode = bind(_udpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(udpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwDebug(WSAGetLastError());
		abort();
	}

	freeaddrinfo(addressInfo);

	return true;
}

tuple<int, int, long long, string> NetworkingClient::_waitForTcpMessage(SOCKET socket) const
{
	char buffer[NetworkingHelper::MAX_TCP_BUFFER_SIZE] = {};
	const auto bufferLength = static_cast<int>(NetworkingHelper::MAX_TCP_BUFFER_SIZE);
	const auto receiveResult = recv(socket, buffer, bufferLength, 0);

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
	sockaddr_in sourceAddress = {};
	char buffer[NetworkingHelper::MAX_UDP_BUFFER_SIZE] = {};
	auto sourceAddressLength = static_cast<int>(sizeof(sourceAddress));

	const auto bufferLength = static_cast<int>(NetworkingHelper::MAX_UDP_BUFFER_SIZE);
	const auto receiveResult = recvfrom(socket, buffer, bufferLength, 0, reinterpret_cast<sockaddr *>(&sourceAddress), &sourceAddressLength);
	const auto ip = NetworkingHelper::_extractAddressIp(sourceAddress);
	const auto port = NetworkingHelper::_extractAddressPort(sourceAddress);

	if(receiveResult > 0)
	{
		return make_tuple(receiveResult, WSAGetLastError(), string(buffer, receiveResult), ip, port);
	}
	else
	{
		return make_tuple(receiveResult, WSAGetLastError(), "", ip, port);
	}
}