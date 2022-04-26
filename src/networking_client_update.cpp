#define WIN32_LEAN_AND_MEAN

#include "networking_client.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <ws2tcpip.h>

using std::future_status;
using std::launch;
using std::chrono::seconds;
using std::get;

void NetworkingClient::update()
{
	if(!_isRunning)
	{
		return;
	}

	if(_mustDisconnectFromServer)
	{
		disconnectFromServer(false);

		return;
	}

	_pendingMessages.clear();

	if(_isConnectingToServer)
	{
		if(_connectionThread.wait_for(seconds(0)) == future_status::ready)
		{
			auto connectionErrorCode = _connectionThread.get();

			if(connectionErrorCode == 0)
			{
				_isConnectingToServer = false;
				_isConnectedToServer = true;

				if(!_sendTcpMessageToServer(("REQUEST" + NetworkingHelper::_extractSocketPort(_udpSocket) + _username), true, false))
				{
					return;
				}

				_tcpMessageThread = async(launch::async, &NetworkingClient::_waitForTcpMessage, this, _tcpSocket);
			}
			else if((connectionErrorCode == WSAECONNREFUSED) || (connectionErrorCode == WSAETIMEDOUT))
			{
				_isConnectingToServer = false;
			}
			else
			{
				Logger::throwDebug(connectionErrorCode);

				abort();
			}
		}
		else
		{
			return;
		}
	}

	if(!_isConnectedToServer)
	{
		return;
	}

	if(_isAcceptedByServer && !_isWaitingForPing)
	{
		if(!_sendTcpMessageToServer("PING", true, true))
		{
			return;
		}

		_isWaitingForPing = true;
		_lastMilliseconds = Tools::getTimeSinceEpochMS();
	}

	if(_tcpMessageThread.wait_for(seconds(0)) == future_status::ready)
	{
		const auto messageResult = _tcpMessageThread.get();
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
					if(_tcpMessageBuild == "ACCEPT")
					{
						_isAcceptedByServer = true;
						_tcpMessageBuild = "";
					}
					else if(_tcpMessageBuild.substr(0, string("PING").size()) == "PING")
					{
						auto latency = (Tools::getTimeSinceEpochMS() - _lastMilliseconds);

						auto serverReceiveDelay = stoll(_tcpMessageBuild.substr(4));
						auto clientReceiveDelay = (Tools::getTimeSinceEpochMS() - messageTimestamp);
						latency -= serverReceiveDelay;
						latency -= clientReceiveDelay;

						if(_pingLatencies.size() == MAX_PING_COUNT)
						{
							_pingLatencies.erase(_pingLatencies.begin());
						}
						_pingLatencies.push_back(static_cast<unsigned int>(llabs(latency)));
						_isWaitingForPing = false;
						_tcpMessageBuild = "";
					}
					else if(_tcpMessageBuild == "SERVER_FULL")
					{
						_pendingMessages.push_back(NetworkingServerMessage(_tcpMessageBuild, NetworkingProtocolType::TCP));
						_tcpMessageBuild = "";
						_mustDisconnectFromServer = true;

						break;
					}
					else if(_tcpMessageBuild == "ALREADY_CONNECTED")
					{
						_pendingMessages.push_back(NetworkingServerMessage(_tcpMessageBuild, NetworkingProtocolType::TCP));
						_tcpMessageBuild = "";
						_mustDisconnectFromServer = true;

						break;
					}
					else if(_tcpMessageBuild == "DISCONNECTED")
					{
						_pendingMessages.push_back(NetworkingServerMessage(_tcpMessageBuild, NetworkingProtocolType::TCP));
						_tcpMessageBuild = "";
						_mustDisconnectFromServer = true;

						break;
					}
					else
					{
						_pendingMessages.push_back(NetworkingServerMessage(_tcpMessageBuild, NetworkingProtocolType::TCP));
						_tcpMessageBuild = "";
					}
				}
				else
				{
					_tcpMessageBuild += character;
				}
			}

			_tcpMessageThread = async(launch::async, &NetworkingClient::_waitForTcpMessage, this, _tcpSocket);
		}
		else if(messageStatusCode == 0)
		{
			disconnectFromServer(false);

			return;
		}
		else
		{
			if((messageErrorCode == WSAECONNRESET) || (messageErrorCode == WSAECONNABORTED) || (messageErrorCode == WSAETIMEDOUT))
			{
				disconnectFromServer(false);

				return;
			}
			else
			{
				Logger::throwDebug(messageErrorCode);

				abort();
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
			if((messageIp == _serverIp) && (messagePort == NetworkingHelper::SERVER_PORT))
			{
				_pendingMessages.push_back(NetworkingServerMessage(messageContent, NetworkingProtocolType::UDP));
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