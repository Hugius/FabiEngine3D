#include "engine_interface.hpp"
#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::client_isRunning() const
{
	return _core->getNetworkingClient()->isRunning();
}

const bool EngineInterface::client_isConnecting() const
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to get connecting status: not running!");
		return false;
	}

	return _core->getNetworkingClient()->isConnectingToServer();
}

const bool EngineInterface::client_isConnected() const
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to get connection status: not running!");
		return false;
	}

	return _core->getNetworkingClient()->isConnectedToServer();
}

const bool EngineInterface::client_isAccepted() const
{
	return _core->getNetworkingClient()->isAcceptedByServer();
}

const unsigned int EngineInterface::client_getPingLatency() const
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to get ping latency: not running!");
		return 0;
	}
	if(!_core->getNetworkingClient()->isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to get ping latency: not connected!");
		return 0;
	}
	if(!_core->getNetworkingClient()->isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to get ping latency: not accepted!");
		return 0;
	}

	return _core->getNetworkingClient()->getPingLatency();
}

const bool EngineInterface::client_isValidServerIP(const string& serverIP) const
{
	return _core->getNetworkingClient()->isValidServerIP(serverIP);
}

const string EngineInterface::client_getUsername() const
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to get username: not running!");
		return "";
	}

	return _core->getNetworkingClient()->getUsername();
}

const string EngineInterface::client_getServerIP() const
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to get server IP: not running!");
		return "";
	}
	if(!_core->getNetworkingClient()->isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to get server IP: not connected!");
		return "";
	}
	if(!_core->getNetworkingClient()->isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to get server IP: not accepted!");
		return "";
	}

	return _core->getNetworkingClient()->getServerIP();
}

const vector<NetworkingServerMessage> EngineInterface::client_getPendingMessages() const
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to get pending messages: not running!");
		return {};
	}

	return _core->getNetworkingClient()->getPendingMessages();
}