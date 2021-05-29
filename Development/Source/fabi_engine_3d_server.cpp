#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkServer_start()
{
	_core->_networkServerTCP.start();
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

const vector<NetworkMessage>& FabiEngine3D::networkServer_getPendingMessages()
{
	return _core->_networkServerTCP.getPendingMessages();
}