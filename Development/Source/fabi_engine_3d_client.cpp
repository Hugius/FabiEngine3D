#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkClient_start(const string& username)
{
	_core->_networkClientTCP.start(username);
}

void FabiEngine3D::networkClient_connect(const string& serverIP)
{
	_core->_networkClientTCP.connectToServer(serverIP, NetworkUtils::SERVER_PORT);
}

void FabiEngine3D::networkClient_sendMessage(const string& content)
{
	_core->_networkClientTCP.sendMessage(content);
}

void FabiEngine3D::networkClient_disconnect()
{
	_core->_networkClientTCP.disconnectFromServer();
}

void FabiEngine3D::networkClient_stop()
{
	_core->_networkClientTCP.stop();
}

const bool FabiEngine3D::networkClient_isRunning()
{
	return _core->_networkClientTCP.isRunning();
}

const bool FabiEngine3D::networkClient_isConnecting()
{
	return _core->_networkClientTCP.isConnectingToServer();
}

const bool FabiEngine3D::networkClient_isConnected()
{
	return _core->_networkClientTCP.isConnectedToServer();
}

const unsigned int FabiEngine3D::networkClient_getServerPing()
{
	return _core->_networkClientTCP.getServerPing();
}

const vector<string>& FabiEngine3D::networkClient_getPendingMessages()
{
	return _core->_networkClientTCP.getPendingMessages();
}