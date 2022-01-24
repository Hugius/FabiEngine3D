#define WIN32_LEAN_AND_MEAN

#include "networking_server.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::to_string;
using std::get;
using std::future_status;
using std::launch;
using std::chrono::system_clock;

void NetworkingServer::update()
{
	if(!_isRunning)
	{
		return;
	}

	_newClientIP = "";
	_newClientUsername = "";

	if(!_oldClientIPs.empty())
	{
		_oldClientIPs.erase(_oldClientIPs.begin());
	}
	if(!_oldClientUsernames.empty())
	{
		_oldClientUsernames.erase(_oldClientUsernames.begin());
	}

	_pendingMessages.clear();

	if(_connectionThread.wait_until(system_clock::time_point::min()) == future_status::ready)
	{
		auto clientSocketID = _connectionThread.get();
		if(clientSocketID == INVALID_SOCKET)
		{
			Logger::throwError("NetworkingServer::update::1 ---> ", WSAGetLastError());
		}

		auto clientIP = NetworkingUtils::extractPeerIP(clientSocketID);
		auto clientPort = NetworkingUtils::extractPeerPort(clientSocketID);

		_clientSockets.push_back(clientSocketID);
		_clientIPs.push_back(clientIP);
		_tcpClientPorts.push_back(clientPort);
		_udpClientPorts.push_back("");
		_clientUsernames.push_back("");
		_tcpMessageBuilds.push_back("");

		_tcpMessageThreads.push_back(async(launch::async, &NetworkingServer::_waitForTcpMessage, this, clientSocketID));

		_connectionThread = async(launch::async, &NetworkingServer::_waitForClientConnection, this, _tcpSocket);
	}

	for(size_t i = 0; i < _clientSockets.size(); i++)
	{
		const auto clientSocketID = _clientSockets[i];
		const auto clientUsername = _clientUsernames[i];

		auto& clientMessageBuild = _tcpMessageBuilds[i];
		auto& messageThread = _tcpMessageThreads[i];

		if(messageThread.wait_until(system_clock::time_point::min()) == future_status::ready)
		{
			const auto messageResult = messageThread.get();
			const auto messageStatusCode = get<0>(messageResult);
			const auto messageErrorCode = get<1>(messageResult);
			const auto messageTimestamp = get<2>(messageResult);
			const auto messageContent = get<3>(messageResult);

			if(messageStatusCode > 0)
			{
				for(const auto& character : messageContent)
				{
					if(character == ';')
					{
						if(clientMessageBuild.substr(0, string("REQUEST").size()) == "REQUEST")
						{
							const auto newPortUDP = clientMessageBuild.substr(string("REQUEST").size(), NetworkingUtils::PORT_DIGIT_COUNT);
							const auto newUsername = clientMessageBuild.substr(string("REQUEST").size() + NetworkingUtils::PORT_DIGIT_COUNT);

							if(_clientIPs.size() > _maxClientCount)
							{
								if(!_sendTcpMessage(clientSocketID, "SERVER_FULL", true))
								{
									return;
								}

								clientMessageBuild = "";

								break;
							}
							else if(find(_clientUsernames.begin(), _clientUsernames.end(), newUsername) != _clientUsernames.end())
							{
								if(!_sendTcpMessage(clientSocketID, "ALREADY_CONNECTED", true))
								{
									return;
								}

								clientMessageBuild = "";

								break;
							}
							else
							{
								if(!_sendTcpMessage(clientSocketID, "ACCEPT", true))
								{
									return;
								}

								_udpClientPorts[i] = newPortUDP;

								_clientUsernames[i] = newUsername;

								_newClientIP = _clientIPs[i];
								_newClientUsername = _clientUsernames[i];
								clientMessageBuild = "";

								Logger::throwInfo("Networking client \"" + newUsername + "\" connected to the server!");
							}
						}
						else if(clientMessageBuild == "PING")
						{
							auto receiveDelay = (Tools::getTimeSinceEpochMS() - messageTimestamp);

							auto pingMessage = ("PING" + to_string(receiveDelay));

							if(!_sendTcpMessage(clientSocketID, pingMessage, true))
							{
								return;
							}

							clientMessageBuild = "";
						}
						else
						{
							_pendingMessages.push_back(NetworkingClientMessage(clientUsername, clientMessageBuild, NetworkProtocol::TCP));
							clientMessageBuild = "";
						}
					}
					else
					{
						clientMessageBuild += character;
					}
				}
			}
			else if(messageStatusCode == 0)
			{
				_disconnectClient(clientSocketID);
				i--;
			}
			else
			{
				auto code = messageErrorCode;
				if((code == WSAECONNRESET) || (code == WSAECONNABORTED) || (code == WSAETIMEDOUT))
				{
					_disconnectClient(clientSocketID);
					i--;
				}
				else
				{
					Logger::throwError("NetworkingServer::update::2 ---> ", messageErrorCode);
				}
			}

			messageThread = async(launch::async, &NetworkingServer::_waitForTcpMessage, this, clientSocketID);
		}
	}

	while(NetworkingUtils::isMessageReadyUDP(_udpSocket))
	{
		const auto messageResult = _receiveUdpMessage(_udpSocket);
		const auto messageStatusCode = get<0>(messageResult);
		const auto messageErrorCode = get<1>(messageResult);
		const auto messageContent = get<2>(messageResult);
		const auto messageIP = get<3>(messageResult);
		const auto messagePort = get<4>(messageResult);

		if(messageStatusCode > 0)
		{
			if(find(_clientIPs.begin(), _clientIPs.end(), messageIP) != _clientIPs.end())
			{
				if(find(_udpClientPorts.begin(), _udpClientPorts.end(), messagePort) != _udpClientPorts.end())
				{
					auto username = messageContent.substr(0, messageContent.find(';'));
					auto content = messageContent.substr(messageContent.find(';') + 1);

					for(size_t i = 0; i < _clientUsernames.size(); i++)
					{
						if(username == _clientUsernames[i])
						{
							_pendingMessages.push_back(NetworkingClientMessage(username, content, NetworkProtocol::UDP));
							break;
						}
					}
				}
			}
		}
		else if
			(
			(messageStatusCode == 0) ||
			(messageErrorCode == WSAECONNRESET) ||
			(messageErrorCode == WSAECONNABORTED) ||
			(messageErrorCode == WSAEMSGSIZE)
			)
		{
		}
		else
		{
			Logger::throwError("NetworkingServer::update::3 ---> ", messageErrorCode);
		}
	}
}