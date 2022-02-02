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

	for(size_t i = 0; i < _clientSockets.size(); i++)
	{
		if(_tcpMessageThreads[i].wait_until(system_clock::time_point::min()) == future_status::ready)
		{
			const auto messageResult = _tcpMessageThreads[i].get();
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
						if(_tcpMessageBuilds[i].substr(0, string("REQUEST").size()) == "REQUEST")
						{
							const auto newPortUDP = _tcpMessageBuilds[i].substr(string("REQUEST").size(), PORT_DIGIT_COUNT);
							const auto newUsername = _tcpMessageBuilds[i].substr(string("REQUEST").size() + PORT_DIGIT_COUNT);

							if(_clientIps.size() > _maxClientCount)
							{
								if(!_sendTcpMessageToClient(_clientSockets[i], "SERVER_FULL", true))
								{
									return;
								}

								_tcpMessageBuilds[i] = "";

								break;
							}
							else if(find(_clientUsernames.begin(), _clientUsernames.end(), newUsername) != _clientUsernames.end())
							{
								if(!_sendTcpMessageToClient(_clientSockets[i], "ALREADY_CONNECTED", true))
								{
									return;
								}

								_tcpMessageBuilds[i] = "";

								break;
							}
							else
							{
								if(!_sendTcpMessageToClient(_clientSockets[i], "ACCEPT", true))
								{
									return;
								}

								_udpClientPorts[i] = newPortUDP;

								_clientUsernames[i] = newUsername;

								_newClientIp = _clientIps[i];
								_newClientUsername = _clientUsernames[i];
								_tcpMessageBuilds[i] = "";

								Logger::throwInfo("Networking client \"" + newUsername + "\" connected to the server!");
							}
						}
						else if(_tcpMessageBuilds[i] == "PING")
						{
							auto receiveDelay = (Tools::getTimeSinceEpochMS() - messageTimestamp);

							auto pingMessage = ("PING" + to_string(receiveDelay));

							if(!_sendTcpMessageToClient(_clientSockets[i], pingMessage, true))
							{
								return;
							}

							_tcpMessageBuilds[i] = "";
						}
						else
						{
							_pendingMessages.push_back(NetworkingClientMessage(_clientUsernames[i], _tcpMessageBuilds[i], NetworkProtocol::TCP));
							_tcpMessageBuilds[i] = "";
						}
					}
					else
					{
						_tcpMessageBuilds[i] += character;
					}
				}
			}
			else if(messageStatusCode == 0)
			{
				_disconnectClient(_clientSockets[i]);
				i--;
			}
			else
			{
				auto code = messageErrorCode;
				if((code == WSAECONNRESET) || (code == WSAECONNABORTED) || (code == WSAETIMEDOUT))
				{
					_disconnectClient(_clientSockets[i]);
					i--;
				}
				else
				{
					Logger::throwDebug(messageErrorCode);
					abort();
				}
			}

			_tcpMessageThreads[i] = async(launch::async, &NetworkingServer::_waitForTcpMessage, this, _clientSockets[i]);
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