#define WIN32_LEAN_AND_MEAN

#include "network_client.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

void NetworkClient::update()
{
	// Must be running first
	if (!_isRunning)
	{
		return;
	}

	// Clear all received messages from last frame
	_receivedMessageQueue.clear();

	// Handle server connection
	if (!_isConnectedToServer)
	{
		if (_connectionThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			// Temporary values
			auto errorCode = _connectionThread.get();

			if (errorCode == 0) // Successfully connected with server
			{
				_isConnectedToServer = true;
			}
			else if (errorCode == WSAECONNREFUSED) // Cannot connect with server
			{
				// Spawn thread again for another attempt
				_spawnConnectionThread();
			}
			else // Something really bad happened
			{
				Logger::throwError("Networking client connect failed with error code: ", errorCode);
			}
		}
	}
}