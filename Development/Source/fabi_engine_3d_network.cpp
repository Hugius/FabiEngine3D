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

void FabiEngine3D::network_loadNextServerRequest()
{
	_core->_networkServer.loadNextRequest();
}

bool FabiEngine3D::network_isStarted()
{
	return (_core->_networkServer.isRunning() || false);
}

bool FabiEngine3D::network_isServerRequestPending()
{
	return _core->_networkServer.isRequestPending();
}

const shared_ptr<NetworkRequest> FabiEngine3D::network_getLatestServerRequest()
{
	return _core->_networkServer.getPendingRequest();
}