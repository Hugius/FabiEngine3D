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