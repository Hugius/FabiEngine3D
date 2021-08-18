#include "fabi_engine_3d.hpp"
#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkClient_start(const string& username)
{
	_core->_networkClientAPI.start(username);
}

void FabiEngine3D::networkClient_connect(const string& serverIP)
{
	_core->_networkClientAPI.connectToServer(serverIP, NetworkUtils::SERVER_PORT);
}

void FabiEngine3D::networkClient_sendMessageTCP(const string& content)
{
	_core->_networkClientAPI.sendTcpMessage(content);
}

void FabiEngine3D::networkClient_sendMessageUDP(const string& content)
{
	_core->_networkClientAPI.sendUdpMessage(content);
}

void FabiEngine3D::networkClient_disconnect()
{
	_core->_networkClientAPI.disconnectFromServer();
}

void FabiEngine3D::networkClient_stop()
{
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

const unsigned int FabiEngine3D::networkClient_getPingLatency()
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve ping latency: not running!");
		return 0;
	}
	if (!_core->_networkClientAPI.isConnectedToServer() || !_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to retrieve ping latency: not connected!");
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

const string& FabiEngine3D::networkClient_getServerIP()
{
	if (!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not running!");
		return "";
	}
	if (!_core->_networkClientAPI.isConnectedToServer() || !_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not connected!");
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