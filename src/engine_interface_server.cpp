#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::server_start(unsigned int maxClientCount)
{
	_core->getNetworkingServer()->start(maxClientCount);
}

void EngineInterface::server_stop()
{
	_core->getNetworkingServer()->stop();
}

void EngineInterface::server_sendTcpMessage(const string& username, const string& content)
{
	_core->getNetworkingServer()->sendTcpMessage(username, content);
}

void EngineInterface::server_sendUdpMessage(const string& username, const string& content)
{
	_core->getNetworkingServer()->sendUdpMessage(username, content);
}

void EngineInterface::server_broadcastTcpMessage(const string& content)
{
	_core->getNetworkingServer()->broadcastTcpMessage(content);
}

void EngineInterface::server_broadcastUdpMessage(const string& content)
{
	_core->getNetworkingServer()->broadcastUdpMessage(content);
}

void EngineInterface::server_disconnectClient(const string& username)
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

const bool EngineInterface::server_isClientConnected(const string& username) const
{
	return _core->getNetworkingServer()->isClientConnected(username);
}

const bool EngineInterface::server_isMessageReserved(const string& message)
{
	return _core->getNetworkingServer()->isMessageReserved(message);
}

const string EngineInterface::server_getNewClientIP() const
{
	return _core->getNetworkingServer()->getNewClientIP();
}

const string EngineInterface::server_getNewClientUsername() const
{
	return _core->getNetworkingServer()->getNewClientUsername();
}

const string EngineInterface::server_getOldClientIP() const
{
	return _core->getNetworkingServer()->getOldClientIP();
}

const string EngineInterface::server_getOldClientUsername() const
{
	return _core->getNetworkingServer()->getOldClientUsername();
}

const unsigned int EngineInterface::server_getMaxMessageSize() const
{
	return _core->getNetworkingServer()->getMaxMessageSize();
}

const vector<NetworkingClientMessage> EngineInterface::server_getPendingMessages() const
{
	return _core->getNetworkingServer()->getPendingMessages();
}

const vector<string> EngineInterface::server_getClientIPs() const
{
	return _core->getNetworkingServer()->getClientIPs();
}

const vector<string> EngineInterface::server_getClientUsernames() const
{
	return _core->getNetworkingServer()->getClientUsernames();
}