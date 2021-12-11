#include "fe3d.hpp"
#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::client_isRunning() const
{
	return _core->_networkClientAPI.isRunning();
}

const bool FabiEngine3D::client_isConnecting() const
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to get connecting status: not running!");
		return false;
	}

	return _core->_networkClientAPI.isConnectingToServer();
}

const bool FabiEngine3D::client_isConnected() const
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to get connection status: not running!");
		return false;
	}

	return _core->_networkClientAPI.isConnectedToServer();
}

const bool FabiEngine3D::client_isAccepted() const
{
	return _core->_networkClientAPI.isAcceptedByServer();
}

const unsigned int FabiEngine3D::client_getPingLatency() const
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to get ping latency: not running!");
		return 0;
	}
	if(!_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to get ping latency: not connected!");
		return 0;
	}
	if(!_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to get ping latency: not accepted!");
		return 0;
	}

	return _core->_networkClientAPI.getPingLatency();
}

const bool FabiEngine3D::client_isValidServerIP(const string& serverIP) const
{
	return _core->_networkClientAPI.isValidServerIP(serverIP);
}

const string FabiEngine3D::client_getUsername() const
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to get username: not running!");
		return "";
	}

	return _core->_networkClientAPI.getUsername();
}

const string FabiEngine3D::client_getServerIP() const
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to get server IP: not running!");
		return "";
	}
	if(!_core->_networkClientAPI.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to get server IP: not connected!");
		return "";
	}
	if(!_core->_networkClientAPI.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to get server IP: not accepted!");
		return "";
	}

	return _core->_networkClientAPI.getServerIP();
}

const vector<NetworkServerMessage> FabiEngine3D::client_getPendingMessages() const
{
	if(!_core->_networkClientAPI.isRunning())
	{
		Logger::throwWarning("Networking client tried to get pending messages: not running!");
		return {};
	}

	return _core->_networkClientAPI.getPendingMessages();
}