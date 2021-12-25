#define WIN32_LEAN_AND_MEAN

#include "networking_server.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::launch;

const bool NetworkingServer::_sendTcpMessage(SOCKET socket, const string& content, bool isReserved)
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::_sendTcpMessage::1");
	}

	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkingServer::_sendTcpMessage::2");
	}
	else if(NetworkingUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkingServer::_sendTcpMessage::3");
	}
	else if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkingServer::_sendTcpMessage::4");
	}

	string message = (content + ';');

	auto sendStatusCode = send(socket, message.c_str(), static_cast<int>(message.size()), 0);

	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAECONNABORTED)
		{
			_disconnectClient(socket);
			return false;
		}
		else if(WSAGetLastError() == WSAENOBUFS)
		{
			Logger::throwWarning("Networking server is sending too many TCP messages!");
		}
		else
		{
			Logger::throwError("NetworkingServer::_sendTcpMessage::5 ---> ", WSAGetLastError());
		}
	}

	return true;
}

const bool NetworkingServer::_sendUdpMessage(const string& clientIP, const string& clientPort, const string& content, bool isReserved) const
{
	if(!_isRunning)
	{
		Logger::throwError("NetworkingServer::_sendUdpMessage::1");
	}

	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkingServer::_sendUdpMessage::2");
	}
	else if(NetworkingUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkingServer::_sendUdpMessage::3");
	}
	else if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkingServer::_sendUdpMessage::4");
	}

	auto socketAddress = NetworkingUtils::composeSocketAddress(clientIP, clientPort);

	auto sendStatusCode = sendto(
		_udpSocket,
		content.c_str(),
		static_cast<int>(content.size()),
		0,
		reinterpret_cast<sockaddr*>(&socketAddress),
		sizeof(socketAddress));

	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAENOBUFS)
		{
			Logger::throwWarning("Networking server is sending too many UDP messages!");
		}
		else
		{
			Logger::throwError("NetworkingServer::_sendUdpMessage::5 ---> ", WSAGetLastError());
		}
	}

	return true;
}

void NetworkingServer::_disconnectClient(SOCKET socket)
{
	for(size_t i = 0; i < _clientSockets.size(); i++)
	{
		if(socket == _clientSockets[i])
		{
			auto clientUsername = _clientUsernames[i];

			closesocket(socket);

			_oldClientIPs.push_back(_clientIPs[i]);
			_oldClientUsernames.push_back(_clientUsernames[i]);

			_clientSockets.erase(_clientSockets.begin() + i);
			_clientIPs.erase(_clientIPs.begin() + i);
			_tcpClientPorts.erase(_tcpClientPorts.begin() + i);
			_udpClientPorts.erase(_udpClientPorts.begin() + i);
			_clientUsernames.erase(_clientUsernames.begin() + i);
			_tcpMessageBuilds.erase(_tcpMessageBuilds.begin() + i);
			_tcpMessageThreads.erase(_tcpMessageThreads.begin() + i);

			if(!clientUsername.empty())
			{
				Logger::throwInfo("Networking client \"" + clientUsername + "\" lost connection with the server!");
			}

			return;
		}
	}
}

const SOCKET NetworkingServer::_waitForClientConnection(SOCKET socket) const
{
	return accept(socket, nullptr, nullptr);
}

tuple<int, int, long long, string> NetworkingServer::_waitForTcpMessage(SOCKET socket) const
{
	char buffer[NetworkingUtils::TCP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkingUtils::TCP_BUFFER_BYTES);
	auto receiveStatusCode = recv(socket, buffer, bufferLength, 0);

	if(receiveStatusCode > 0)
	{
		return make_tuple(receiveStatusCode, 0, Tools::getTimeSinceEpochMS(), string(buffer, receiveStatusCode));
	}
	else if(receiveStatusCode == 0)
	{
		return make_tuple(receiveStatusCode, 0, Tools::getTimeSinceEpochMS(), "");
	}
	else
	{
		return make_tuple(receiveStatusCode, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, string, string, string> NetworkingServer::_receiveUdpMessage(SOCKET socket) const
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