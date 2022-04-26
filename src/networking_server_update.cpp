#define WIN32_LEAN_AND_MEAN

#include "networking_server.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <ws2tcpip.h>

using std::to_string;
using std::get;
using std::future_status;
using std::launch;
using std::chrono::seconds;

void NetworkingServer::update()
{
	if(!_isRunning)
	{
		return;
	}

	_newClientIp = "";
	_newClientUsername = "";

	if(!_oldClientIps.empty())
	{
		_oldClientIps.erase(_oldClientIps.begin());
	}
	if(!_oldClientUsernames.empty())
	{
		_oldClientUsernames.erase(_oldClientUsernames.begin());
	}

	_pendingMessages.clear();

	if(_connectionThread.wait_for(seconds(0)) == future_status::ready)
	{
		const auto clientSocket = _connectionThread.get();

		if(clientSocket == INVALID_SOCKET)
		{
			Logger::throwDebug(WSAGetLastError());

			abort();
		}

		const auto clientIp = NetworkingHelper::_extractPeerIp(clientSocket);
		const auto clientPort = NetworkingHelper::_extractPeerPort(clientSocket);

		_clientSockets.push_back(clientSocket);
		_clientIps.push_back(clientIp);
		_tcpClientPorts.push_back(clientPort);
		_udpClientPorts.push_back("");
		_clientUsernames.push_back("");
		_tcpMessageBuilds.push_back("");

		_tcpMessageThreads.push_back(async(launch::async, &NetworkingServer::_waitForTcpMessage, this, clientSocket));

		_connectionThread = async(launch::async, &NetworkingServer::_waitForClientConnection, this, _tcpSocket);
	}

	for(int index = 0; index < static_cast<int>(_clientSockets.size()); index++)
	{
		if(_tcpMessageThreads[index].wait_for(seconds(0)) == future_status::ready)
		{
			const auto messageResult = _tcpMessageThreads[index].get();
			const auto messageStatusCode = get<0>(messageResult);
			const auto messageErrorCode = get<1>(messageResult);
			const auto messageTimestamp = get<2>(messageResult);
			const auto messageContent = get<3>(messageResult);

			if(messageStatusCode > 0)
			{
				for(const auto & character : messageContent)
				{
					if(character == ';')
					{
						if(_tcpMessageBuilds[index].substr(0, string("REQUEST").size()) == "REQUEST")
						{
							const auto newUdpPort = _tcpMessageBuilds[index].substr(string("REQUEST").size(), NetworkingHelper::SERVER_PORT.size());
							const auto newUsername = _tcpMessageBuilds[index].substr(string("REQUEST").size() + NetworkingHelper::SERVER_PORT.size());

							if(_clientIps.size() > _maxClientCount)
							{
								if(!_sendTcpMessageToClient(_clientSockets[index], "SERVER_FULL", true))
								{
									return;
								}

								_tcpMessageBuilds[index] = "";

								break;
							}
							else if(find(_clientUsernames.begin(), _clientUsernames.end(), newUsername) != _clientUsernames.end())
							{
								if(!_sendTcpMessageToClient(_clientSockets[index], "ALREADY_CONNECTED", true))
								{
									return;
								}

								_tcpMessageBuilds[index] = "";

								break;
							}
							else
							{
								if(!_sendTcpMessageToClient(_clientSockets[index], "ACCEPT", true))
								{
									return;
								}

								_udpClientPorts[index] = newUdpPort;

								_clientUsernames[index] = newUsername;

								_newClientIp = _clientIps[index];
								_newClientUsername = _clientUsernames[index];
								_tcpMessageBuilds[index] = "";

								Logger::throwInfo("Networking client \"" + newUsername + "\" connected to the server");
							}
						}
						else if(_tcpMessageBuilds[index] == "PING")
						{
							auto receiveDelay = (Tools::getTimeSinceEpochMS() - messageTimestamp);

							auto pingMessage = ("PING" + to_string(receiveDelay));

							if(!_sendTcpMessageToClient(_clientSockets[index], pingMessage, true))
							{
								return;
							}

							_tcpMessageBuilds[index] = "";
						}
						else
						{
							_pendingMessages.push_back(NetworkingClientMessage(_clientUsernames[index], _tcpMessageBuilds[index], NetworkingProtocolType::TCP));
							_tcpMessageBuilds[index] = "";
						}
					}
					else
					{
						_tcpMessageBuilds[index] += character;
					}
				}

				_tcpMessageThreads[index] = async(launch::async, &NetworkingServer::_waitForTcpMessage, this, _clientSockets[index]);
			}
			else if(messageStatusCode == 0)
			{
				_disconnectClient(_clientSockets[index]);
				index--;
			}
			else
			{
				if((messageErrorCode == WSAECONNRESET) || (messageErrorCode == WSAECONNABORTED) || (messageErrorCode == WSAETIMEDOUT))
				{
					_disconnectClient(_clientSockets[index]);
					index--;
				}
				else
				{
					Logger::throwDebug(messageErrorCode);

					abort();
				}
			}
		}
	}

	while(NetworkingHelper::_isUdpMessageReady(_udpSocket))
	{
		const auto messageResult = _receiveUdpMessage(_udpSocket);
		const auto messageStatusCode = get<0>(messageResult);
		const auto messageErrorCode = get<1>(messageResult);
		const auto messageContent = get<2>(messageResult);
		const auto messageIp = get<3>(messageResult);
		const auto messagePort = get<4>(messageResult);

		if(messageStatusCode > 0)
		{
			if(find(_clientIps.begin(), _clientIps.end(), messageIp) != _clientIps.end())
			{
				if(find(_udpClientPorts.begin(), _udpClientPorts.end(), messagePort) != _udpClientPorts.end())
				{
					auto username = messageContent.substr(0, messageContent.find(';'));
					auto content = messageContent.substr(messageContent.find(';') + 1);

					for(int index = 0; index < static_cast<int>(_clientUsernames.size()); index++)
					{
						if(username == _clientUsernames[index])
						{
							_pendingMessages.push_back(NetworkingClientMessage(username, content, NetworkingProtocolType::UDP));

							break;
						}
					}
				}
			}
		}
		else if((messageStatusCode == 0) || (messageErrorCode == WSAECONNRESET) || (messageErrorCode == WSAECONNABORTED) || (messageErrorCode == WSAEMSGSIZE))
		{
			// Purposely left blank
		}
		else
		{
			Logger::throwDebug(messageErrorCode);

			abort();
		}
	}
}