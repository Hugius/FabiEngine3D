#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkServer_start(unsigned int customMaxClientCount)
{
	_core->_networkServerTCP.start(customMaxClientCount);
}

void FabiEngine3D::networkServer_stop()
{
	if (networkServer_isStarted())
	{
		_core->_networkServerTCP.stop();
	}
	else
	{
		logger_throwWarning("Trying to stop networking server: not started!");
	}
}

void FabiEngine3D::networkServer_sendMessage(const NetworkMessage& message)
{
	_core->_networkServerTCP.sendMessage(message);
}

void FabiEngine3D::networkServer_broadcastMessage(const string& content)
{
	_core->_networkServerTCP.broadcastMessage(content);
}

const bool FabiEngine3D::networkServer_isStarted()
{
	return _core->_networkServerTCP.isRunning();
}

const bool FabiEngine3D::networkServer_isClientConnected(const string& ipAddress, const string& port)
{
	return _core->_networkServerTCP.isClientConnected(ipAddress, port);
}

const vector<NetworkMessage>& FabiEngine3D::networkServer_getPendingMessages()
{
	return _core->_networkServerTCP.getPendingMessages();
}

const vector<string>& FabiEngine3D::networkServer_getClientIPs()
{
	return _core->_networkServerTCP.getClientIPs();
}

const vector<string>& FabiEngine3D::networkServer_getClientPorts()
{
	return _core->_networkServerTCP.getClientPorts();
}