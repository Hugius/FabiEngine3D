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

	// Handle server connection
	if (!_isConnectedToServer)
	{
		if (_connectionThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
		{
			// Temporary values
			auto connectionErrorCode = _connectionThread.get();

			if (connectionErrorCode == 0) // Successfully connected with server
			{
				_isConnectedToServer = true;
			}
			else if (connectionErrorCode == WSAECONNREFUSED) // Cannot connect with server
			{
				// Spawn thread again for another attempt
				_connectionThread = std::async(std::launch::async, &NetworkClient::_connectWithServer, this, _serverSocketID, _addressInfo);
			}
			else // Something really bad happened
			{
				Logger::throwError("Networking client connect failed with error code: ", connectionErrorCode);
			}
		}
	}
}