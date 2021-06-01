#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkServer_start(unsigned int customMaxClientCount)
{
	_core->_networkServerTCP.start(customMaxClientCount);
}

void FabiEngine3D::networkServer_stop()
{
	_core->_networkServerTCP.stop();
}

void FabiEngine3D::networkServer_sendMessage(const string& username, const string& content)
{
	_core->_networkServerTCP.sendMessage(username, content);
}

void FabiEngine3D::networkServer_broadcastMessage(const string& content)
{
	_core->_networkServerTCP.broadcastMessage(content);
}

void FabiEngine3D::networkServer_disconnectClient(const string& username)
{
	_core->_networkServerTCP.disconnectClient(username);
}

const bool FabiEngine3D::networkServer_isRunning()
{
	return _core->_networkServerTCP.isRunning();
}

const bool FabiEngine3D::networkServer_isClientConnected(const string& username)
{
	return _core->_networkServerTCP.isClientConnected(username);
}

const vector<NetworkMessage>& FabiEngine3D::networkServer_getPendingMessages()
{
	return _core->_networkServerTCP.getPendingMessages();
}

const vector<string> FabiEngine3D::networkServer_getClientIPs()
{
	return _core->_networkServerTCP.getClientIPs();
}

const vector<string> FabiEngine3D::networkServer_getClientPorts()
{
	return _core->_networkServerTCP.getClientPorts();
}

const vector<string> FabiEngine3D::networkServer_getClientUsernames()
{
	return _core->_networkServerTCP.getClientUsernames();
}