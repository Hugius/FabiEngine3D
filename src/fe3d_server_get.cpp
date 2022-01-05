#include "fe3d.hpp"
#include "core.hpp"

const bool FabiEngine3D::server_isRunning() const
{
	return _core->_networkingServer->isRunning();
}

const bool FabiEngine3D::server_isClientConnected(const string& username) const
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to get client connection status: not running!");
		return false;
	}

	return _core->_networkingServer->isClientConnected(username);
}

const string FabiEngine3D::server_getNewClientIP() const
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to get new client IP: not running!");
		return "";
	}

	return _core->_networkingServer->getNewClientIP();
}

const string FabiEngine3D::server_getNewClientUsername() const
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to get new client username: not running!");
		return "";
	}

	return _core->_networkingServer->getNewClientUsername();
}

const string FabiEngine3D::server_getOldClientIP() const
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to get old client IP: not running!");
		return "";
	}

	return _core->_networkingServer->getOldClientIP();
}

const string FabiEngine3D::server_getOldClientUsername() const
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to get old client username: not running!");
		return "";
	}

	return _core->_networkingServer->getOldClientUsername();
}

const vector<NetworkingClientMessage> FabiEngine3D::server_getPendingMessages() const
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to get pending messages: not running!");
		return {};
	}

	return _core->_networkingServer->getPendingMessages();
}

const vector<string> FabiEngine3D::server_getClientIPs() const
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to get client IPs: not running!");
		return {};
	}

	return _core->_networkingServer->getClientIPs();
}

const vector<string> FabiEngine3D::server_getClientUsernames() const
{
	if(!_core->_networkingServer->isRunning())
	{
		Logger::throwWarning("Networking server tried to get client usernames: not running!");
		return {};
	}

	return _core->_networkingServer->getClientUsernames();
}