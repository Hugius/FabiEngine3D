#include "fabi_engine_3d.hpp"
#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkClient_start(const string& username)
{
	_core->_networkClientAPI.start(username);
}

void FabiEngine3D::networkClient_connect(const string& serverIP)
{
	_core->_networkClientAPI.connectToServer(serverIP, NetworkUtils::SERVER_PORT);
}

void FabiEngine3D::networkClient_sendMessageTCP(const string& content)
{
	_core->_networkClientAPI.sendTcpMessage(content);
}

void FabiEngine3D::networkClient_sendMessageUDP(const string& content)
{
	_core->_networkClientAPI.sendUdpMessage(content);
}

void FabiEngine3D::networkClient_disconnect()
{
	_core->_networkClientAPI.disconnectFromServer();
}

void FabiEngine3D::networkClient_stop()
{
	_core->_networkClientAPI.stop();
}

const bool FabiEngine3D::networkClient_isRunning()
{
	return _core->_networkClientAPI.isRunning();
}

const bool FabiEngine3D::networkClient_isConnecting()
{
	return _core->_networkClientAPI.isConnectingToServer();
}

const bool FabiEngine3D::networkClient_isConnected()
{
	return _core->_networkClientAPI.isConnectedToServer();
}

const unsigned int FabiEngine3D::networkClient_getPingLatency()
{
	return _core->_networkClientAPI.getPingLatency();
}

const bool FabiEngine3D::networkClient_isValidServerIP(const string& serverIP)
{
	return _core->_networkClientAPI.isValidServerIP(serverIP);
}

const string& FabiEngine3D::networkClient_getUsername()
{
	return _core->_networkClientAPI.getUsername();
}

const string& FabiEngine3D::networkClient_getServerIP()
{
	return _core->_networkClientAPI.getServerIP();
}

const vector<NetworkServerMessage>& FabiEngine3D::networkClient_getPendingMessages()
{
	return _core->_networkClientAPI.getPendingMessages();
}