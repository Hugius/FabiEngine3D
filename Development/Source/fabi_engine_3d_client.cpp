#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkClient_start(const string& serverIP)
{
	_core->_networkClientTCP.start(serverIP, NetworkServerTCP::SERVER_PORT);
}

void FabiEngine3D::networkClient_stop()
{
	if (networkClient_isStarted())
	{
		_core->_networkClientTCP.stop();
	}
	else
	{
		logger_throwWarning("Trying to stop networking client: not started!");
	}
}

void FabiEngine3D::networkClient_sendMessage(const string& content)
{
	_core->_networkClientTCP.sendMessage(content);
}

const bool FabiEngine3D::networkClient_isStarted()
{
	return _core->_networkClientTCP.isRunning();
}

const bool FabiEngine3D::networkClient_isConnected()
{
	return _core->_networkClientTCP.isConnected();
}

const bool FabiEngine3D::networkClient_isMessagePending()
{
	return _core->_networkClientTCP.isMessagePending();
}

const shared_ptr<NetworkMessage> FabiEngine3D::networkClient_getPendingMessage()
{
	return _core->_networkClientTCP.getPendingMessage();
}