#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkClient_start(const string& serverIP, const string& username)
{
	_core->_networkClientTCP.start(serverIP, NetworkUtils::SERVER_PORT, username);
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

const bool FabiEngine3D::networkClient_isConnectedToServer()
{
	return _core->_networkClientTCP.isConnectedToServer();
}

const unsigned int FabiEngine3D::networkClient_getPingMS()
{
	return _core->_networkClientTCP.getPingMS();
}

const vector<NetworkMessage>& FabiEngine3D::networkClient_getPendingMessages()
{
	return _core->_networkClientTCP.getPendingMessages();
}