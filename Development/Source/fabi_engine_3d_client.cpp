#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkClient_start(const string& serverIP)
{
	_core->_networkClient.start(serverIP, NetworkServer::networkServer_PORT);
}

void FabiEngine3D::networkClient_stop()
{
	if (networkClient_isStarted())
	{
		_core->_networkClient.stop();
	}
	else
	{
		logger_throwWarning("Trying to stop networking client: not started!");
	}
}

void FabiEngine3D::networkClient_loadNextPendingMessage()
{
	_core->_networkClient.loadNextPendingMessage();
}

void FabiEngine3D::networkClient_sendMessage(const string& content)
{
	_core->_networkClient.sendMessage(content);
}

bool FabiEngine3D::networkClient_isConnectedToServer()
{
	return _core->_networkClient.isConnectedToServer();
}

bool FabiEngine3D::networkClient_isMessagePending()
{
	return _core->_networkClient.isMessagePending();
}

const shared_ptr<NetworkMessage> FabiEngine3D::networkClient_getPendingMessage()
{
	return _core->_networkClient.getPendingMessage();
}