#define WIN32_LEAN_AND_MEAN

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

	const auto message = (content + ';');
	const auto sendStatusCode = send(_tcpSocket, message.c_str(), static_cast<int>(message.size()), 0);

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

	auto socketAddress = NetworkingHelper::_getSocketAddress(_serverIp, NetworkingHelper::SERVER_PORT);

	const auto message = (_username + ';' + content);
	const auto sendStatusCode = sendto(_udpSocket, message.c_str(), static_cast<int>(message.size()), 0, reinterpret_cast<sockaddr *>(&socketAddress), sizeof(socketAddress));

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

const int NetworkingClient::_connectToServer(SOCKET socket, const string & ip) const
{
	auto socketAddress = NetworkingHelper::_getSocketAddress(ip, NetworkingHelper::SERVER_PORT);

	const auto connectStatusCode = connect(socket, reinterpret_cast<sockaddr *>(&socketAddress), sizeof(socketAddress));

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
	addrinfo hints = {};

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	addrinfo * addressInfo = nullptr;

	const auto tcpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);

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

	const auto tcpBindStatusCode = bind(_tcpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));

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
	addrinfo hints = {};

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	addrinfo * addressInfo = nullptr;

	const auto udpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);

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

	const auto udpBindStatusCode = bind(_udpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));

	if(udpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwDebug(WSAGetLastError());

		abort();
	}

	freeaddrinfo(addressInfo);

	return true;
}

tuple<int, int, long long, string> NetworkingClient::_getTcpMessage(SOCKET socket) const
{
	char buffer[NetworkingHelper::MAX_TCP_BUFFER_SIZE] = {};

	const auto receiveResult = recv(socket, buffer, NetworkingHelper::MAX_TCP_BUFFER_SIZE, 0);

	if(receiveResult > 0)
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), string(buffer, receiveResult));
	}
	else
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, string, string, string> NetworkingClient::_getUdpMessage(SOCKET socket) const
{
	sockaddr_in sourceAddress = {};
	char buffer[NetworkingHelper::MAX_UDP_BUFFER_SIZE] = {};

	auto sourceAddressLength = static_cast<int>(sizeof(sourceAddress));

	const auto receiveResult = recvfrom(socket, buffer, NetworkingHelper::MAX_UDP_BUFFER_SIZE, 0, reinterpret_cast<sockaddr *>(&sourceAddress), &sourceAddressLength);
	const auto ip = NetworkingHelper::_getAddressIp(sourceAddress);
	const auto port = NetworkingHelper::_getAddressPort(sourceAddress);

	if(receiveResult > 0)
	{
		return make_tuple(receiveResult, WSAGetLastError(), string(buffer, receiveResult), ip, port);
	}
	else
	{
		return make_tuple(receiveResult, WSAGetLastError(), "", ip, port);
	}
}