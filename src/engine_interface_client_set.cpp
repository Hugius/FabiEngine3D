#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::client_start(const string& username)
{
	if(_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to start: already running!");
		return;
	}
	if(username.empty())
	{
		Logger::throwWarning("Networking client tried to start: username is empty!");
		return;
	}
	if(username.size() > NetworkingUtils::MAX_USERNAME_CHARACTERS)
	{
		Logger::throwWarning("Networking client tried to start: username is too long!");
		return;
	}
	if(NetworkingUtils::isMessageReserved(username))
	{
		Logger::throwWarning("Networking client tried to start: username is reserved!");
		return;
	}
	if(find(username.begin(), username.end(), ';') != username.end())
	{
		Logger::throwWarning("Networking client tried to start: username cannot contain ':'!");
		return;
	}

	_core->getNetworkingClient()->start(username);
}

void EngineInterface::client_connect(const string& serverIP)
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to connect: not running!");
		return;
	}
	if(_core->getNetworkingClient()->isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to connect: already connected!");
		return;
	}
	if(_core->getNetworkingClient()->isConnectingToServer())
	{
		Logger::throwWarning("Networking client tried to connect: already connecting!");
		return;
	}
	if(!_core->getNetworkingClient()->isValidServerIP(serverIP))
	{
		Logger::throwWarning("Networking client tried to connect: invalid server IP!");
		return;
	}

	_core->getNetworkingClient()->connectToServer(serverIP, NetworkingUtils::SERVER_PORT);
}

void EngineInterface::client_sendTcpMessage(const string& content)
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to send TCP message: not running!");
		return;
	}
	if(!_core->getNetworkingClient()->isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to send TCP message: not connected!");
		return;
	}
	if(!_core->getNetworkingClient()->isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to send TCP message: not accepted!");
		return;
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking client tried to send TCP message: cannot contain ':'!");
		return;
	}
	if(NetworkingUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking client tried to send TCP message: \"" + content + "\" is reserved!");
		return;
	}
	if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking client tried to send TCP message: maximum character amount exceeded!");
		return;
	}

	_core->getNetworkingClient()->sendTcpMessage(content);
}

void EngineInterface::client_sendUdpMessage(const string& content)
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to send UDP message: not running!");
		return;
	}
	if(!_core->getNetworkingClient()->isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to send UDP message: not connected!");
		return;
	}
	if(!_core->getNetworkingClient()->isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to send UDP message: not accepted!");
		return;
	}
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking client tried to send UDP message: cannot contain ':'!");
		return;
	}
	if(NetworkingUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking client tried to send UDP message: \"" + content + "\" is reserved!");
		return;
	}
	if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking client tried to send UDP message: maximum character amount exceeded!");
		return;
	}

	_core->getNetworkingClient()->sendUdpMessage(content);
}

void EngineInterface::client_disconnect()
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to disconnect: not running!");
		return;
	}
	if(!_core->getNetworkingClient()->isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to disconnect: not connected!");
		return;
	}
	if(!_core->getNetworkingClient()->isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to disconnect: not accepted!");
		return;
	}

	_core->getNetworkingClient()->disconnectFromServer(true);
}

void EngineInterface::client_stop()
{
	if(!_core->getNetworkingClient()->isRunning())
	{
		Logger::throwWarning("Networking client tried to stop: not running!");
		return;
	}

	_core->getNetworkingClient()->stop();
}