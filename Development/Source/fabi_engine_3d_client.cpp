#include "fabi_engine_3d.hpp"
#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkClient_start(const string& username)
{
	if (_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to start: already running!");
		return;
	}
	if (username.empty())
	{
		Logger::throwWarning("Networking client tried to start: username is empty!");
		return;
	}
	if (username.size() > NetworkUtils::MAX_USERNAME_CHARACTERS)
	{
		Logger::throwWarning("Networking client tried to start: username is too long!");
		return;
	}
	if (NetworkUtils::isMessageReserved(username))
	{
		Logger::throwWarning("Networking client tried to start: username is reserved!");
		return;
	}
	if (find(username.begin(), username.end(), ';') != username.end())
	{
		Logger::throwWarning("Networking client tried to start: username cannot contain semicolons!");
		return;
	}

	_core->_networkClientAPI.start(username);
}

void FabiEngine3D::networkClient_connect(const string& serverIP)
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to connect: not running!");
		return;
	}
	if (_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to connect: already connected!");
		return;
	}
	if (_core->_networkClientAPI.isConnectingToServer())
	{
		Logger::throwWarning("Networking client tried to connect: already connecting!");
		return;
	}
	if (!_core->_networkClientAPI.isValidServerIP(serverIP))
	{
		Logger::throwWarning("Networking client tried to connect: invalid server IP!");
		return;
	}

	_core->_networkClientAPI.connectToServer(serverIP, NetworkUtils::SERVER_PORT);
}

void FabiEngine3D::networkClient_sendMessageTCP(const string& content)
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to send TCP message: not running!");
		return;
	}
	if (!_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to send TCP message: not connected!");
		return;
	}
	if (!_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to send TCP message: not accepted!");
		return;
	}
	if (find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking client tried to send TCP message: cannot contain semicolons!");
		return;
	}
	if (NetworkUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking client tried to send TCP message: \"" + content + "\" is reserved!");
		return;
	}
	if (content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking client tried to send TCP message: maximum character amount exceeded!");
		return;
	}

	_core->_networkClientAPI.sendTcpMessage(content);
}

void FabiEngine3D::networkClient_sendMessageUDP(const string& content)
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to send UDP message: not running!");
		return;
	}
	if (!_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to send UDP message: not connected!");
		return;
	}
	if (!_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to send UDP message: not accepted!");
		return;
	}
	if (find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking client tried to send UDP message: cannot contain semicolons!");
		return;
	}
	if (NetworkUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking client tried to send UDP message: \"" + content + "\" is reserved!");
		return;
	}
	if (content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking client tried to send UDP message: maximum character amount exceeded!");
		return;
	}

	_core->_networkClientAPI.sendUdpMessage(content);
}

void FabiEngine3D::networkClient_disconnect()
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to disconnect: not running!");
		return;
	}
	if (!_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to disconnect: not connected!");
		return;
	}
	if (!_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to disconnect: not accepted!");
		return;
	}

	_core->_networkClientAPI.disconnectFromServer();
}

void FabiEngine3D::networkClient_stop()
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to stop: not running!");
		return;
	}

	_core->_networkClientAPI.stop();
}

const bool FabiEngine3D::networkClient_isRunning()
{
	return _core->_networkClientAPI.isRunning();
}

const bool FabiEngine3D::networkClient_isConnecting()
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve connecting status: not running!");
		return false;
	}

	return _core->_networkClientAPI.isConnectingToServer();
}

const bool FabiEngine3D::networkClient_isConnected()
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve connection status: not running!");
		return false;
	}

	return _core->_networkClientAPI.isConnectedToServer();
}

const bool FabiEngine3D::networkClient_isAccepted()
{
	return _core->_networkClientAPI.isAcceptedByServer();
}

const unsigned int FabiEngine3D::networkClient_getPingLatency()
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve ping latency: not running!");
		return 0;
	}
	if (!_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to retrieve ping latency: not connected!");
		return 0;
	}
	if (!_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to retrieve ping latency: not accepted!");
		return 0;
	}

	return _core->_networkClientAPI.getPingLatency();
}

const bool FabiEngine3D::networkClient_isValidServerIP(const string& serverIP)
{
	return _core->_networkClientAPI.isValidServerIP(serverIP);
}

const string& FabiEngine3D::networkClient_getUsername()
{
	return _core->_networkClientAPI.getUsername();
}

const string FabiEngine3D::networkClient_getServerIP()
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not running!");
		return "";
	}
	if (!_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not connected!");
		return "";
	}
	if (!_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not accepted!");
		return "";
	}

	return _core->_networkClientAPI.getServerIP();
}

const vector<NetworkServerMessage> FabiEngine3D::networkClient_getPendingMessages()
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve pending messages: not running!");
		return {};
	}

	return _core->_networkClientAPI.getPendingMessages();
}