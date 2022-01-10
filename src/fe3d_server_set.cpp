#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::server_start(unsigned int maxClientCount)
{
	if(_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to start: already running!");
		return;
	}
	if(maxClientCount <= 0)
	{
		Logger::throwWarning("Networking server tried to start: invalid maximum client count!");
		return;
	}

	_core->getNetworkingServer()->start(maxClientCount);
}

void EngineInterface::server_stop()
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to stop: not running!");
		return;
	}

	_core->getNetworkingServer()->stop();
}

void EngineInterface::server_sendTcpMessage(const string& username, const string& content)
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to send TCP message to client \"" + username + "\": not running!");
		return;
	}
	if(!_core->getNetworkingServer()->isClientConnected(username))
	{
		Logger::throwWarning("Networking server tried to send TCP message to client \"" + username + "\": not connected!");
		return;
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking message tried to send TCP message: cannot contain ':'!");
		return;
	}
	else if(NetworkingUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking server tried to send TCP message: \"" + content + "\" is reserved!");
		return;
	}
	else if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking server tried to send TCP message: maximum character amount exceeded!");
		return;
	}

	_core->getNetworkingServer()->sendTcpMessage(username, content);
}

void EngineInterface::server_sendUdpMessage(const string& username, const string& content)
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to send UDP message to client \"" + username + "\": not running!");
		return;
	}
	if(!_core->getNetworkingServer()->isClientConnected(username))
	{
		Logger::throwWarning("Networking server tried to send UDP message to client \"" + username + "\": not connected!");
		return;
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking message tried to send UDP message: cannot contain ':'!");
		return;
	}
	else if(NetworkingUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking server tried to send UDP message: \"" + content + "\" is reserved!");
		return;
	}
	else if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking server tried to send UDP message: maximum character amount exceeded!");
		return;
	}

	_core->getNetworkingServer()->sendUdpMessage(username, content);
}

void EngineInterface::server_broadcastTcpMessage(const string& content, const string& exceptionUsername)
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to broadcast TCP message: not running!");
		return;
	}

	_core->getNetworkingServer()->broadcastTcpMessage(content, exceptionUsername);
}

void EngineInterface::server_broadcastUdpMessage(const string& content, const string& exceptionUsername)
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to broadcast UDP message: not running!");
		return;
	}

	_core->getNetworkingServer()->broadcastUdpMessage(content, exceptionUsername);
}

void EngineInterface::server_disconnectClient(const string& username)
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to disconnect client \"" + username + "\": not running!");
		return;
	}
	if(!_core->getNetworkingServer()->isClientConnected(username))
	{
		Logger::throwWarning("Networking server tried to disconnect client \"" + username + "\": not connected!");
		return;
	}

	_core->getNetworkingServer()->disconnectClient(username);
}

void EngineInterface::server_disconnectClients()
{
	if(!_core->getNetworkingServer()->isRunning())
	{
		Logger::throwWarning("Networking server tried to disconnect clients: not running!");
		return;
	}

	_core->getNetworkingServer()->disconnectClients();
}