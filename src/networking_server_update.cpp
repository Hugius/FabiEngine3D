#define WIN32_LEAN_AND_MEAN

#include "networking_server.hpp"
#include "logger.hpp"
#include "tools.hpp"

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

	if(_connectionThread.wait_until(system_clock::time_point::min()) == future_status::ready)
	{
		const auto clientSocket = _connectionThread.get();

		if(clientSocket == INVALID_SOCKET)
		{
			Logger::throwDebug(WSAGetLastError());
			abort();
		}

		const auto clientIp = _extractPeerIp(clientSocket);
		const auto clientPort = _extractPeerPort(clientSocket);

		_clientSockets.push_back(clientSocket);
		_clientIps.push_back(clientIp);
		_tcpClientPorts.push_back(clientPort);
		_udpClientPorts.push_back("");
		_clientUsernames.push_back("");
		_tcpMessageBuilds.push_back("");

		_tcpMessageThreads.push_back(async(launch::async, &NetworkingServer::_waitForTcpMessage, this, clientSocket));

		_connectionThread = async(launch::async, &NetworkingServer::_waitForClientConnection, this, _tcpSocket);
	}

	for(unsigned int index = 0; index < _clientSockets.size(); index++)
	{
		if(_tcpMessageThreads[index].wait_until(system_clock::time_point::min()) == future_status::ready)
		{
			const auto messageResult = _tcpMessageThreads[index].get();
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
						if(_tcpMessageBuilds[index].substr(0, string("REQUEST").size()) == "REQUEST")
						{
							const auto newPortUDP = _tcpMessageBuilds[index].substr(string("REQUEST").size(), PORT_DIGIT_COUNT);
							const auto newUsername = _tcpMessageBuilds[index].substr(string("REQUEST").size() + PORT_DIGIT_COUNT);

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

								_udpClientPorts[index] = newPortUDP;

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
							_pendingMessages.push_back(NetworkingClientMessage(_clientUsernames[index], _tcpMessageBuilds[index], NetworkProtocol::TCP));
							_tcpMessageBuilds[index] = "";
						}
					}
					else
					{
						_tcpMessageBuilds[index] += character;
					}
				}
			}
			else if(messageStatusCode == 0)
			{
				_disconnectClient(_clientSockets[index]);
				index--;
			}
			else
			{
				auto code = messageErrorCode;
				if((code == WSAECONNRESET) || (code == WSAECONNABORTED) || (code == WSAETIMEDOUT))
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

			_tcpMessageThreads[index] = async(launch::async, &NetworkingServer::_waitForTcpMessage, this, _clientSockets[index]);
		}
	}

	while(_isMessageReadyUDP(_udpSocket))
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

					for(unsigned int index = 0; index < _clientUsernames.size(); index++)
					{
						if(username == _clientUsernames[index])
						{
							_pendingMessages.push_back(NetworkingClientMessage(username, content, NetworkProtocol::UDP));
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