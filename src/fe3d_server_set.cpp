#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::server_start(unsigned int maxClientCount)
{
	if(_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to start: already running!");
		return;
	}
	if(maxClientCount <= 0)
	{
		Logger::throwWarning("Networking server tried to start: invalid maximum client count!");
		return;
	}

	_core->_networkingServer->start(maxClientCount);
}

void FabiEngine3D::server_stop()
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to stop: not running!");
		return;
	}

	_core->_networkingServer->stop();
}

void FabiEngine3D::server_sendTcpMessage(const string& username, const string& content)
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to send TCP message to client \"" + username + "\": not running!");
		return;
	}
	if(!_core->_networkingServer->isClientConnected(username))
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

	_core->_networkingServer->sendTcpMessage(username, content);
}

void FabiEngine3D::server_sendUdpMessage(const string& username, const string& content)
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to send UDP message to client \"" + username + "\": not running!");
		return;
	}
	if(!_core->_networkingServer->isClientConnected(username))
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

	_core->_networkingServer->sendUdpMessage(username, content);
}

void FabiEngine3D::server_broadcastTcpMessage(const string& content, const string& exceptionUsername)
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to broadcast TCP message: not running!");
		return;
	}

	_core->_networkingServer->broadcastTcpMessage(content, exceptionUsername);
}

void FabiEngine3D::server_broadcastUdpMessage(const string& content, const string& exceptionUsername)
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to broadcast UDP message: not running!");
		return;
	}

	_core->_networkingServer->broadcastUdpMessage(content, exceptionUsername);
}

void FabiEngine3D::server_disconnectClient(const string& username)
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to disconnect client \"" + username + "\": not running!");
		return;
	}
	if(!_core->_networkingServer->isClientConnected(username))
	{
		Logger::throwWarning("Networking server tried to disconnect client \"" + username + "\": not connected!");
		return;
	}

	_core->_networkingServer->disconnectClient(username);
}

void FabiEngine3D::server_disconnectClients()
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to disconnect clients: not running!");
		return;
	}

	_core->_networkingServer->disconnectClients();
}