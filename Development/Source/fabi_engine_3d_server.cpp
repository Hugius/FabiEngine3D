#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networknetworkServer_start()
{
	_core->_networkServer.start();
}

void FabiEngine3D::networkServer_stop()
{
	if (networkServer_isStarted())
	{
		_core->_networkServer.stop();
	}
	else
	{
		logger_throwWarning("Trying to stop networking server: not started!");
	}
}

void FabiEngine3D::networkServer_loadNextPendingMessage()
{
	_core->_networkServer.loadNextPendingMessage();
}

void FabiEngine3D::networkClient_sendMessageToClient(const string& ipAddress, const string& content)
{
	_core->_networkServer.sendMessageToClient(ipAddress, content);
}

void FabiEngine3D::networkClient_broadcastMessage(const string& content)
{
	_core->_networkServer.broadcastMessage(content);
}

const bool FabiEngine3D::networkServer_isStarted()
{
	return _core->_networkServer.isRunning();
}

const bool FabiEngine3D::networkServer_isMessagePending()
{
	return _core->_networkServer.isMessagePending();
}

const shared_ptr<NetworkMessage> FabiEngine3D::networkServer_getPendingMessage()
{
	return _core->_networkServer.getPendingMessage();
}