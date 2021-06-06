#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::networkServer_start(unsigned int customMaxClientCount)
{
	_core->_networkServerAPI.start(customMaxClientCount);
}

void FabiEngine3D::networkServer_stop()
{
	_core->_networkServerAPI.stop();
}

void FabiEngine3D::networkServer_sendMessageTCP(const string& username, const string& content)
{
	_core->_networkServerAPI.sendTcpMessage(username, content);
}

void FabiEngine3D::networkServer_sendMessageUDP(const string& username, const string& content)
{
	_core->_networkServerAPI.sendUdpMessage(username, content);
}

void FabiEngine3D::networkServer_broadcastMessageTCP(const string& content)
{
	_core->_networkServerAPI.broadcastTcpMessage(content);
}

void FabiEngine3D::networkServer_broadcastMessageUDP(const string& content)
{
	_core->_networkServerAPI.broadcastUdpMessage(content);
}

void FabiEngine3D::networkServer_disconnectClient(const string& username)
{
	_core->_networkServerAPI.disconnectClient(username);
}

const bool FabiEngine3D::networkServer_isRunning()
{
	return _core->_networkServerAPI.isRunning();
}

const bool FabiEngine3D::networkServer_isClientConnected(const string& username)
{
	return _core->_networkServerAPI.isClientConnected(username);
}

const vector<NetworkClientMessage>& FabiEngine3D::networkServer_getPendingMessages()
{
	return _core->_networkServerAPI.getPendingMessages();
}

const vector<string> FabiEngine3D::networkServer_getClientIPs()
{
	return _core->_networkServerAPI.getClientIPs();
}

const vector<string> FabiEngine3D::networkServer_getClientPorts()
{
	return _core->_networkServerAPI.getClientPorts();
}

const vector<string> FabiEngine3D::networkServer_getClientUsernames()
{
	return _core->_networkServerAPI.getClientUsernames();
}