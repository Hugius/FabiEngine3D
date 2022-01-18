#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::server_isRunning() const
{
	return _core->getNetworkingServer()->isRunning();
}

const bool EngineInterface::server_isClientConnected(const string& username) const
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to get client connection status: not running!");
		return false;
	}

	return _core->getNetworkingServer()->isClientConnected(username);
}

const string EngineInterface::server_getNewClientIP() const
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to get new client IP: not running!");
		return "";
	}

	return _core->getNetworkingServer()->getNewClientIP();
}

const string EngineInterface::server_getNewClientUsername() const
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to get new client username: not running!");
		return "";
	}

	return _core->getNetworkingServer()->getNewClientUsername();
}

const string EngineInterface::server_getOldClientIP() const
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to get old client IP: not running!");
		return "";
	}

	return _core->getNetworkingServer()->getOldClientIP();
}

const string EngineInterface::server_getOldClientUsername() const
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to get old client username: not running!");
		return "";
	}

	return _core->getNetworkingServer()->getOldClientUsername();
}

const vector<NetworkingClientMessage> EngineInterface::server_getPendingMessages() const
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to get pending messages: not running!");
		return {};
	}

	return _core->getNetworkingServer()->getPendingMessages();
}

const vector<string> EngineInterface::server_getClientIPs() const
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to get client IPs: not running!");
		return {};
	}

	return _core->getNetworkingServer()->getClientIPs();
}

const vector<string> EngineInterface::server_getClientUsernames() const
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to get client usernames: not running!");
		return {};
	}

	return _core->getNetworkingServer()->getClientUsernames();
}