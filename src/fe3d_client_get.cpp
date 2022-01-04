#include "fe3d.hpp"
#include "fe3d.hpp"
#include "core.hpp"

const bool FabiEngine3D::client_isRunning() const
{
	return _core->_networkingClient.isRunning();
}

const bool FabiEngine3D::client_isConnecting() const
{
	if(!_core->_networkingClient.isRunning())
	{
		Logger::throwWarning("Networking client tried to get connecting status: not running!");
		return false;
	}

	return _core->_networkingClient.isConnectingToServer();
}

const bool FabiEngine3D::client_isConnected() const
{
	if(!_core->_networkingClient.isRunning())
	{
		Logger::throwWarning("Networking client tried to get connection status: not running!");
		return false;
	}

	return _core->_networkingClient.isConnectedToServer();
}

const bool FabiEngine3D::client_isAccepted() const
{
	return _core->_networkingClient.isAcceptedByServer();
}

const unsigned int FabiEngine3D::client_getPingLatency() const
{
	if(!_core->_networkingClient.isRunning())
	{
		Logger::throwWarning("Networking client tried to get ping latency: not running!");
		return 0;
	}
	if(!_core->_networkingClient.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to get ping latency: not connected!");
		return 0;
	}
	if(!_core->_networkingClient.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to get ping latency: not accepted!");
		return 0;
	}

	return _core->_networkingClient.getPingLatency();
}

const bool FabiEngine3D::client_isValidServerIP(const string& serverIP) const
{
	return _core->_networkingClient.isValidServerIP(serverIP);
}

const string FabiEngine3D::client_getUsername() const
{
	if(!_core->_networkingClient.isRunning())
	{
		Logger::throwWarning("Networking client tried to get username: not running!");
		return "";
	}

	return _core->_networkingClient.getUsername();
}

const string FabiEngine3D::client_getServerIP() const
{
	if(!_core->_networkingClient.isRunning())
	{
		Logger::throwWarning("Networking client tried to get server IP: not running!");
		return "";
	}
	if(!_core->_networkingClient.isConnectedToServer())
	{
		Logger::throwWarning("Networking client tried to get server IP: not connected!");
		return "";
	}
	if(!_core->_networkingClient.isAcceptedByServer())
	{
		Logger::throwWarning("Networking client tried to get server IP: not accepted!");
		return "";
	}

	return _core->_networkingClient.getServerIP();
}

const vector<NetworkingServerMessage> FabiEngine3D::client_getPendingMessages() const
{
	if(!_core->_networkingClient.isRunning())
	{
		Logger::throwWarning("Networking client tried to get pending messages: not running!");
		return {};
	}

	return _core->_networkingClient.getPendingMessages();
}