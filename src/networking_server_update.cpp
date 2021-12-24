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
	// Must be running
	if(!_isRunning)
	{
		return;
	}

	// Clear new client data from last tick
	_newClientIP = "";
	_newClientUsername = "";

	// Clear old client data from last tick
	if(!_oldClientIPs.empty())
	{
		_oldClientIPs.erase(_oldClientIPs.begin());
	}
	if(!_oldClientUsernames.empty())
	{
		_oldClientUsernames.erase(_oldClientUsernames.begin());
	}

	// Clear all received messages from last tick
	_pendingMessages.clear();

	// Handle new client connections
	if(_connectionThread.wait_until(system_clock::time_point::min()) == future_status::ready)
	{
		// Retrieve new client socket ID
		auto clientSocketID = _connectionThread.get();
		if(clientSocketID == INVALID_SOCKET)
		{
			Logger::throwError("NetworkingServer::update::1 ---> ", WSAGetLastError());
		}

		// Extract IP & port
		auto clientIP = NetworkingUtils::extractPeerIP(clientSocketID);
		auto clientPort = NetworkingUtils::extractPeerPort(clientSocketID);

		// Save client data
		_clientSockets.push_back(clientSocketID);
		_clientIPs.push_back(clientIP);
		_tcpClientPorts.push_back(clientPort);
		_udpClientPorts.push_back("");
		_clientUsernames.push_back("");
		_tcpMessageBuilds.push_back("");

		// Spawn thread for receiving TCP messages
		_tcpMessageThreads.push_back(async(launch::async, &NetworkingServer::_waitForTcpMessage, this, clientSocketID));

		// Spawn connection thread again for next possible client
		_connectionThread = async(launch::async, &NetworkingServer::_waitForClientConnection, this, _tcpSocket);
	}

	// Receive incoming TCP messages
	BEGIN:;
	for(size_t i = 0; i < _clientSockets.size(); i++)
	{
		// Immutable client data
		const auto& clientSocketID = _clientSockets[i];
		const auto& clientUsername = _clientUsernames[i];

		// Mutable client data
		auto& clientMessageBuild = _tcpMessageBuilds[i];
		auto& messageThread = _tcpMessageThreads[i];

		// Check if the client sent any message
		if(messageThread.wait_until(system_clock::time_point::min()) == future_status::ready)
		{
			// Message data
			const auto& messageResult = messageThread.get();
			const auto& messageStatusCode = get<0>(messageResult);
			const auto& messageErrorCode = get<1>(messageResult);
			const auto& messageTimestamp = get<2>(messageResult);
			const auto& messageContent = get<3>(messageResult);

			if(messageStatusCode > 0) // Message is received correctly
			{
				for(const auto& character : messageContent) // Iterate through received messages
				{
					if(character == ';') // End of current message
					{
						if(clientMessageBuild.substr(0, string("REQUEST").size()) == "REQUEST") // Handle REQUEST message
						{
							// Temporary values
							const auto newPortUDP = clientMessageBuild.substr(string("REQUEST").size(), NetworkingUtils::PORT_DIGIT_COUNT);
							const auto newUsername = clientMessageBuild.substr(string("REQUEST").size() + NetworkingUtils::PORT_DIGIT_COUNT);

							// Check if server is full or username is already connected
							if(_clientIPs.size() > _maxClientCount)
							{
								// Reject client
								if(!_sendTcpMessage(clientSocketID, "SERVER_FULL", true))
								{
									return;
								}

								// Miscellaneous
								clientMessageBuild = "";

								// Prevent processing more messages
								break;
							}
							else if(find(_clientUsernames.begin(), _clientUsernames.end(), newUsername) != _clientUsernames.end())
							{
								// Reject client
								if(!_sendTcpMessage(clientSocketID, "ALREADY_CONNECTED", true))
								{
									return;
								}

								// Miscellaneous
								clientMessageBuild = "";

								// Prevent processing more messages
								break;
							}
							else
							{
								// Accept client
								if(!_sendTcpMessage(clientSocketID, "ACCEPT", true))
								{
									return;
								}

								// Save new port
								_udpClientPorts[i] = newPortUDP;

								// Save new username
								_clientUsernames[i] = newUsername;

								// Miscellaneous
								_newClientIP = _clientIPs[i];
								_newClientUsername = _clientUsernames[i];
								clientMessageBuild = "";

								// Logging
								Logger::throwInfo("Networking client \"" + newUsername + "\" connected to the server!");
							}
						}
						else if(clientMessageBuild == "PING") // Handle PING message
						{
							// Calculate delay between receiving the message and processing the receive
							auto receiveDelay = (Tools::getTimeSinceEpochMS() - messageTimestamp);

							// Compose ping message
							auto pingMessage = ("PING" + to_string(receiveDelay));

							// Send ping message back to client
							if(!_sendTcpMessage(clientSocketID, pingMessage, true))
							{
								return;
							}

							// Miscellaneous
							clientMessageBuild = "";
						}
						else // Handle other message
						{
							_pendingMessages.push_back(NetworkingClientMessage(clientUsername, clientMessageBuild, NetworkProtocol::TCP));
							clientMessageBuild = "";
						}
					}
					else // Add to current message build
					{
						clientMessageBuild += character;
					}
				}
			}
			else if(messageStatusCode == 0) // Client closed socket connection
			{
				_disconnectClient(clientSocketID);
				goto BEGIN;
			}
			else // Receive failed
			{
				auto code = messageErrorCode;
				if((code == WSAECONNRESET) || (code == WSAECONNABORTED) || (code == WSAETIMEDOUT)) // Client lost socket connection
				{
					_disconnectClient(clientSocketID);
					goto BEGIN;
				}
				else // Something really bad happened
				{
					Logger::throwError("NetworkingServer::update::2 ---> ", messageErrorCode);
				}
			}

			// Spawn new message thread
			messageThread = async(launch::async, &NetworkingServer::_waitForTcpMessage, this, clientSocketID);
		}
	}

	// Receive incoming UDP messages
	while(NetworkingUtils::isMessageReadyUDP(_udpSocket))
	{
		// Message data
		const auto& messageResult = _receiveUdpMessage(_udpSocket);
		const auto& messageStatusCode = get<0>(messageResult);
		const auto& messageErrorCode = get<1>(messageResult);
		const auto& messageContent = get<2>(messageResult);
		const auto& messageIP = get<3>(messageResult);
		const auto& messagePort = get<4>(messageResult);

		if(messageStatusCode > 0) // Message is received correctly
		{
			if(find(_clientIPs.begin(), _clientIPs.end(), messageIP) != _clientIPs.end()) // Message must come from a client IP
			{
				if(find(_udpClientPorts.begin(), _udpClientPorts.end(), messagePort) != _udpClientPorts.end()) // Message must come from a client port
				{
					// Temporary values
					auto username = messageContent.substr(0, messageContent.find(';'));
					auto content = messageContent.substr(messageContent.find(';') + 1);

					// Try to find client
					for(size_t i = 0; i < _clientUsernames.size(); i++)
					{
						// Check if username matches
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
			// Wrong packet, do nothing
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkingServer::update::3 ---> ", messageErrorCode);
		}
	}
}