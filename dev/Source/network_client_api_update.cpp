#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::future_status;
using std::launch;
using std::chrono::system_clock;
using std::get;

void NetworkClientAPI::update()
{
	// Must be running
	if(!_isRunning)
	{
		return;
	}

	// Check if client must disconnect
	if(_mustDisconnectFromServer)
	{
		disconnectFromServer(false);
		return;
	}

	// Clear all received messages from last tick
	_pendingMessages.clear();

	// Handle server connection
	if(_isConnectingToServer)
	{
		// Check if connection thread is finished
		if(_connectionThread.wait_until(system_clock::time_point::min()) == future_status::ready)
		{
			// Retrieve error code
			auto connectionErrorCode = _connectionThread.get();

			if(connectionErrorCode == 0) // Successfully connected with server
			{
				// Not connecting anymore
				_isConnectingToServer = false;
				_isConnectedToServer = true;

				// Send acceptance request to server
				if(!_sendMessageTCP(("REQUEST" + NetworkUtils::extractSocketPort(_socketUDP) + _username), true, false))
				{
					return;
				}

				// Start a thread to wait for TCP messages
				_messageThreadTCP = async(launch::async, &NetworkClientAPI::_waitForMessageTCP, this, _socketTCP);
			}
			else if((connectionErrorCode == WSAECONNREFUSED) || (connectionErrorCode == WSAETIMEDOUT)) // Cannot connect with server
			{
				_isConnectingToServer = false;
			}
			else // Something really bad happened
			{
				Logger::throwError("NetworkClientAPI::update::1 ---> ", connectionErrorCode);
			}
		}
		else
		{
			return; // Wait until client is connected to server
		}
	}

	// Must be connected
	if(!_isConnectedToServer)
	{
		return;
	}

	// Update server pinging
	if(_isAcceptedByServer && !_isWaitingForPing)
	{
		// Send ping
		if(!_sendMessageTCP("PING", true, true))
		{
			return;
		}

		// Start measuring latency
		_isWaitingForPing = true;
		_lastMilliseconds = Tools::getTimeSinceEpochMS();
	}

	// Receive incoming TCP messages
	if(_messageThreadTCP.wait_until(system_clock::time_point::min()) == future_status::ready)
	{
		// Temporary values
		const auto& messageResult = _messageThreadTCP.get();
		const auto& messageStatusCode = get<0>(messageResult);
		const auto& messageErrorCode = get<1>(messageResult);
		const auto& messageTimestamp = get<2>(messageResult);
		const auto& messageContent = get<3>(messageResult);

		if(messageStatusCode > 0) // Message is received correctly
		{
			for(const auto& character : messageContent) // Loop through received message content
			{
				if(character == ';') // End of current message
				{
					if(_messageBuildTCP == "ACCEPT") // Handle ACCEPT message
					{
						_isAcceptedByServer = true;
						_messageBuildTCP = "";
					}
					else if(_messageBuildTCP.substr(0, string("PING").size()) == "PING") // Handle PING message
					{
						// Calculate ping latency
						auto latency = (Tools::getTimeSinceEpochMS() - _lastMilliseconds);

						// Subtract the server & client processing delays
						auto serverReceiveDelay = stoll(_messageBuildTCP.substr(4));
						auto clientReceiveDelay = (Tools::getTimeSinceEpochMS() - messageTimestamp);
						latency -= serverReceiveDelay;
						latency -= clientReceiveDelay;

						// Register server latency
						if(_pingLatencies.size() == NetworkUtils::MAX_PING_COUNT)
						{
							_pingLatencies.erase(_pingLatencies.begin());
						}
						_pingLatencies.push_back(static_cast<unsigned int>(llabs(latency)));
						_isWaitingForPing = false;
						_messageBuildTCP = "";
					}
					else if(_messageBuildTCP == "SERVER_FULL") // Handle SERVER_FULL message
					{
						// Disconnect next tick
						_pendingMessages.push_back(NetworkServerMessage(_messageBuildTCP, NetworkProtocol::TCP));
						_messageBuildTCP = "";
						_mustDisconnectFromServer = true;

						// Prevent processing more messages
						break;
					}
					else if(_messageBuildTCP == "ALREADY_CONNECTED") // Handle ALREADY_CONNECTED message
					{
						// Disconnect next tick
						_pendingMessages.push_back(NetworkServerMessage(_messageBuildTCP, NetworkProtocol::TCP));
						_messageBuildTCP = "";
						_mustDisconnectFromServer = true;

						// Prevent processing more messages
						break;
					}
					else if(_messageBuildTCP == "DISCONNECTED") // Handle DISCONNECTED message
					{
						// Disconnect next tick
						_pendingMessages.push_back(NetworkServerMessage(_messageBuildTCP, NetworkProtocol::TCP));
						_messageBuildTCP = "";
						_mustDisconnectFromServer = true;

						// Prevent processing more messages
						break;
					}
					else // Handle other message
					{
						_pendingMessages.push_back(NetworkServerMessage(_messageBuildTCP, NetworkProtocol::TCP));
						_messageBuildTCP = "";
					}
				}
				else // Add to current message build
				{
					_messageBuildTCP += character;
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
				Logger::throwError("NetworkClientAPI::update::2 ---> ", code);
			}
		}

		// Spawn new TCP message thread
		_messageThreadTCP = async(launch::async, &NetworkClientAPI::_waitForMessageTCP, this, _socketTCP);
	}

	// Receive incoming UDP messages
	while(NetworkUtils::isMessageReadyUDP(_socketUDP))
	{
		// Message data
		const auto& messageResult = _receiveMessageUDP(_socketUDP);
		const auto& messageStatusCode = get<0>(messageResult);
		const auto& messageErrorCode = get<1>(messageResult);
		const auto& messageContent = get<2>(messageResult);
		const auto& messageIP = get<3>(messageResult);
		const auto& messagePort = get<4>(messageResult);

		if(messageStatusCode > 0) // Message is received correctly
		{
			if((messageIP == _serverIP) && (messagePort == _serverPort)) // Message must come from server
			{
				_pendingMessages.push_back(NetworkServerMessage(messageContent, NetworkProtocol::UDP));
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
			// Wrong packet, do nothing
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkClientAPI::update::3 ---> ", messageErrorCode);
		}
	}
}