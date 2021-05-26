#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::network_start(NetworkPeerType type)
{
	if (type == NetworkPeerType::SERVER)
	{
		_core->_networkServer.start();
	}
	else
	{

	}
}

void FabiEngine3D::network_stop()
{
	if (_core->_networkServer.isRunning())
	{
		_core->_networkServer.stop();
	}
	else if (false)
	{

	}
	else
	{
		logger_throwWarning("Trying to stop networking: not started!");
	}
}

void FabiEngine3D::network_loadNextPendingMessage()
{
	_core->_networkServer.loadNextMessage();
}

bool FabiEngine3D::network_isStarted()
{
	return (_core->_networkServer.isRunning() || false);
}

bool FabiEngine3D::network_isMessagePending()
{
	return _core->_networkServer.isMessagePending();
}

const shared_ptr<NetworkMessage> FabiEngine3D::network_getPendingMessage()
{
	return _core->_networkServer.getPendingMessage();
}