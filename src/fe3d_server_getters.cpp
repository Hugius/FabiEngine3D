#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::networkServer_isRunning() const
{
	return _core->_networkServerAPI.isRunning();
}

const bool FabiEngine3D::networkServer_isClientConnected(const string& username) const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to retrieve client connection status: not running!");
		return false;
	}

	return _core->_networkServerAPI.isClientConnected(username);
}

const string FabiEngine3D::networkServer_getNewClientIP() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to retrieve new client IP: not running!");
		return "";
	}

	return _core->_networkServerAPI.getNewClientIP();
}

const string FabiEngine3D::networkServer_getNewClientUsername() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to retrieve new client username: not running!");
		return "";
	}

	return _core->_networkServerAPI.getNewClientUsername();
}

const string FabiEngine3D::networkServer_getOldClientIP() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to retrieve old client IP: not running!");
		return "";
	}

	return _core->_networkServerAPI.getOldClientIP();
}

const string FabiEngine3D::networkServer_getOldClientUsername() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to retrieve old client username: not running!");
		return "";
	}

	return _core->_networkServerAPI.getOldClientUsername();
}

const vector<NetworkClientMessage> FabiEngine3D::networkServer_getPendingMessages() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to retrieve pending messages: not running!");
		return {};
	}

	return _core->_networkServerAPI.getPendingMessages();
}

const vector<string> FabiEngine3D::networkServer_getClientIPs() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to retrieve client IPs: not running!");
		return {};
	}

	return _core->_networkServerAPI.getClientIPs();
}

const vector<string> FabiEngine3D::networkServer_getClientUsernames() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to retrieve client usernames: not running!");
		return {};
	}

	return _core->_networkServerAPI.getClientUsernames();
}