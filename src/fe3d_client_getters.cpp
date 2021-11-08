#include "fe3d.hpp"
#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::networkClient_isRunning()
{
	return _core->_networkClientAPI.isRunning();
}

const bool FabiEngine3D::networkClient_isConnecting()
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve connecting status: not running!");
		return false;
	}

	return _core->_networkClientAPI.isConnectingToServer();
}

const bool FabiEngine3D::networkClient_isConnected()
{
	if(!_core->_networkClientAPI.isRunning())
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
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve ping latency: not running!");
		return 0;
	}
	if(!_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to retrieve ping latency: not connected!");
		return 0;
	}
	if(!_core->_networkClientAPI.isAcceptedByServer())
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

const string FabiEngine3D::networkClient_getUsername()
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve username: not running!");
		return "";
	}

	return _core->_networkClientAPI.getUsername();
}

const string FabiEngine3D::networkClient_getServerIP()
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not running!");
		return "";
	}
	if(!_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not connected!");
		return "";
	}
	if(!_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to retrieve server IP: not accepted!");
		return "";
	}

	return _core->_networkClientAPI.getServerIP();
}

const vector<NetworkServerMessage> FabiEngine3D::networkClient_getPendingMessages()
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to retrieve pending messages: not running!");
		return {};
	}

	return _core->_networkClientAPI.getPendingMessages();
}