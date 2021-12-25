#define WIN32_LEAN_AND_MEAN

#include "networking_client.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::future_status;
using std::launch;
using std::chrono::system_clock;
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
		if(_connectionThread.wait_until(system_clock::time_point::min()) == future_status::ready)
		{
			auto connectionErrorCode = _connectionThread.get();

			if(connectionErrorCode == 0) // Successfully connected with server
			{
				_isConnectingToServer = false;
				_isConnectedToServer = true;

				if(!_sendTcpMessage(("REQUEST" + NetworkingUtils::extractSocketPort(_udpSocket) + _username), true, false))
				{
					return;
				}

				_tcpMessageThread = async(launch::async, &NetworkingClient::_waitForTcpMessage, this, _tcpSocket);
			}
			else if((connectionErrorCode == WSAECONNREFUSED) || (connectionErrorCode == WSAETIMEDOUT)) // Cannot connect with server
			{
				_isConnectingToServer = false;
			}
			else // Something really bad happened
			{
				Logger::throwError("NetworkingClient::update::1 ---> ", connectionErrorCode);
			}
		}
		else
		{
			return; // Wait until client is connected to server
		}
	}

	if(!_isConnectedToServer)
	{
		return;
	}

	if(_isAcceptedByServer && !_isWaitingForPing)
	{
		if(!_sendTcpMessage("PING", true, true))
		{
			return;
		}

		_isWaitingForPing = true;
		_lastMilliseconds = Tools::getTimeSinceEpochMS();
	}

	if(_tcpMessageThread.wait_until(system_clock::time_point::min()) == future_status::ready)
	{
		const auto& messageResult = _tcpMessageThread.get();
		const auto& messageStatusCode = get<0>(messageResult);
		const auto& messageErrorCode = get<1>(messageResult);
		const auto& messageTimestamp = get<2>(messageResult);
		const auto& messageContent = get<3>(messageResult);

		if(messageStatusCode > 0) // Message is received correctly
		{
			for(const auto& character : messageContent) // Iterate through received message content
			{
				if(character == ';') // End of current message
				{
					if(_tcpMessageBuild == "ACCEPT") // Handle ACCEPT message
					{
						_isAcceptedByServer = true;
						_tcpMessageBuild = "";
					}
					else if(_tcpMessageBuild.substr(0, string("PING").size()) == "PING") // Handle PING message
					{
						auto latency = (Tools::getTimeSinceEpochMS() - _lastMilliseconds);

						auto serverReceiveDelay = stoll(_tcpMessageBuild.substr(4));
						auto clientReceiveDelay = (Tools::getTimeSinceEpochMS() - messageTimestamp);
						latency -= serverReceiveDelay;
						latency -= clientReceiveDelay;

						if(_pingLatencies.size() == NetworkingUtils::MAX_PING_COUNT)
						{
							_pingLatencies.erase(_pingLatencies.begin());
						}
						_pingLatencies.push_back(static_cast<unsigned int>(llabs(latency)));
						_isWaitingForPing = false;
						_tcpMessageBuild = "";
					}
					else if(_tcpMessageBuild == "SERVER_FULL") // Handle SERVER_FULL message
					{
						_pendingMessages.push_back(NetworkingServerMessage(_tcpMessageBuild, NetworkProtocol::TCP));
						_tcpMessageBuild = "";
						_mustDisconnectFromServer = true;

						break;
					}
					else if(_tcpMessageBuild == "ALREADY_CONNECTED") // Handle ALREADY_CONNECTED message
					{
						_pendingMessages.push_back(NetworkingServerMessage(_tcpMessageBuild, NetworkProtocol::TCP));
						_tcpMessageBuild = "";
						_mustDisconnectFromServer = true;

						break;
					}
					else if(_tcpMessageBuild == "DISCONNECTED") // Handle DISCONNECTED message
					{
						_pendingMessages.push_back(NetworkingServerMessage(_tcpMessageBuild, NetworkProtocol::TCP));
						_tcpMessageBuild = "";
						_mustDisconnectFromServer = true;

						break;
					}
					else // Handle other message
					{
						_pendingMessages.push_back(NetworkingServerMessage(_tcpMessageBuild, NetworkProtocol::TCP));
						_tcpMessageBuild = "";
					}
				}
				else // Add to current message build
				{
					_tcpMessageBuild += character;
				}
			}
		}
		else if(messageStatusCode == 0) // Server closed socket connection
		{
			disconnectFromServer(false);
			return;
		}
		else // Receive failed
		{
			auto code = messageErrorCode;
			if((code == WSAECONNRESET) || (code == WSAECONNABORTED) || (code == WSAETIMEDOUT)) // Server lost socket connection
			{
				disconnectFromServer(false);
				return;
			}
			else // Something really bad happened
			{
				Logger::throwError("NetworkingClient::update::2 ---> ", code);
			}
		}

		_tcpMessageThread = async(launch::async, &NetworkingClient::_waitForTcpMessage, this, _tcpSocket);
	}

	while(NetworkingUtils::isMessageReadyUDP(_udpSocket))
	{
		const auto& messageResult = _receiveUdpMessage(_udpSocket);
		const auto& messageStatusCode = get<0>(messageResult);
		const auto& messageErrorCode = get<1>(messageResult);
		const auto& messageContent = get<2>(messageResult);
		const auto& messageIP = get<3>(messageResult);
		const auto& messagePort = get<4>(messageResult);

		if(messageStatusCode > 0) // Message is received correctly
		{
			if((messageIP == _serverIP) && (messagePort == _serverPort)) // Message must come from server
			{
				_pendingMessages.push_back(NetworkingServerMessage(messageContent, NetworkProtocol::UDP));
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
		else // Something really bad happened
		{
			Logger::throwError("NetworkingClient::update::3 ---> ", messageErrorCode);
		}
	}
}