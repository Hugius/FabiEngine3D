#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::server_start(int maxClientCount)
{
	_core->getNetworkingServer()->start(maxClientCount);
}

void EngineInterface::server_stop()
{
	_core->getNetworkingServer()->stop();
}

void EngineInterface::server_sendTcpMessageToClient(const string & username, const string & content)
{
	_core->getNetworkingServer()->sendTcpMessageToClient(username, content);
}

void EngineInterface::server_sendUdpMessageToClient(const string & username, const string & content)
{
	_core->getNetworkingServer()->sendUdpMessageToClient(username, content);
}

void EngineInterface::server_broadcastTcpMessageToClients(const string & content)
{
	_core->getNetworkingServer()->broadcastTcpMessageToClients(content);
}

void EngineInterface::server_broadcastUdpMessageToClients(const string & content)
{
	_core->getNetworkingServer()->broadcastUdpMessageToClients(content);
}

void EngineInterface::server_disconnectClient(const string & username)
{
	_core->getNetworkingServer()->disconnectClient(username);
}

void EngineInterface::server_disconnectClients()
{
	_core->getNetworkingServer()->disconnectClients();
}

const bool EngineInterface::server_isRunning() const
{
	return _core->getNetworkingServer()->isRunning();
}

const bool EngineInterface::server_isClientConnected(const string & username) const
{
	return _core->getNetworkingServer()->isClientConnected(username);
}

const bool EngineInterface::server_isMessageReserved(const string & message)
{
	return _core->getNetworkingHelper()->isMessageReserved(message);
}

const string EngineInterface::server_getNewClientIp() const
{
	return _core->getNetworkingServer()->getNewClientIp();
}

const string EngineInterface::server_getNewClientUsername() const
{
	return _core->getNetworkingServer()->getNewClientUsername();
}

const string EngineInterface::server_getOldClientIp() const
{
	return _core->getNetworkingServer()->getOldClientIp();
}

const string EngineInterface::server_getOldClientUsername() const
{
	return _core->getNetworkingServer()->getOldClientUsername();
}

const int EngineInterface::server_getMaxMessageSize() const
{
	return _core->getNetworkingHelper()->getMaxMessageSize();
}

const vector<NetworkingClientMessage> EngineInterface::server_getPendingMessages() const
{
	return _core->getNetworkingServer()->getPendingMessages();
}

const vector<string> EngineInterface::server_getClientIps() const
{
	return _core->getNetworkingServer()->getClientIps();
}

const vector<string> EngineInterface::server_getClientUsernames() const
{
	return _core->getNetworkingServer()->getClientUsernames();
}