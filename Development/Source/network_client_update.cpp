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
	if (_connectionThread.wait_until(std::chrono::system_clock::time_point::min()) == std::future_status::ready)
	{
		// Temporary values
		auto connectionErrorCode = _connectionThread.get();

		if (connectionErrorCode == 0)
		{
			// Address info not needed anymore
			freeaddrinfo(_addressInfo);
			_addressInfo = nullptr;
		}
		else if(connectionErrorCode == 10061)
		{

		}
		else
		{
			Logger::throwError("Network client connect failed with error code: ", connectionErrorCode);
		}
	}
}