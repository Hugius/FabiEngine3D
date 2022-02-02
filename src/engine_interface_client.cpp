#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::client_start(const string& username)
{
	_core->getNetworkingClient()->start(username);
}

void EngineInterface::client_connectToServer(const string& ip)
{
	_core->getNetworkingClient()->connectToServer(ip);
}

void EngineInterface::client_sendTcpMessageToServer(const string& content)
{
	_core->getNetworkingClient()->sendTcpMessageToServer(content);
}

void EngineInterface::client_sendUdpMessageToServer(const string& content)
{
	_core->getNetworkingClient()->sendUdpMessageToServer(content);
}

void EngineInterface::client_disconnectFromServer()
{
	_core->getNetworkingClient()->disconnectFromServer(true);
}

void EngineInterface::client_stop()
{
	_core->getNetworkingClient()->stop();
}

const bool EngineInterface::client_isRunning() const
{
	return _core->getNetworkingClient()->isRunning();
}

const bool EngineInterface::client_isConnectingToServer() const
{
	return _core->getNetworkingClient()->isConnectingToServer();
}

const bool EngineInterface::client_isConnectedToServer() const
{
	return _core->getNetworkingClient()->isConnectedToServer();
}

const bool EngineInterface::client_isAcceptedByServer() const
{
	return _core->getNetworkingClient()->isAcceptedByServer();
}

const bool EngineInterface::client_isMessageReserved(const string& message)
{
	return _core->getNetworkingClient()->isMessageReserved(message);
}

const unsigned int EngineInterface::client_getPingLatency() const
{
	return _core->getNetworkingClient()->getPingLatency();
}

const unsigned int EngineInterface::client_getMaxUsernameSize() const
{
	return _core->getNetworkingClient()->getMaxUsernameSize();
}

const unsigned int EngineInterface::client_getMaxMessageSize() const
{
	return _core->getNetworkingClient()->getMaxMessageSize();
}

const bool EngineInterface::client_isValidIp(const string& ip) const
{
	return _core->getNetworkingClient()->isValidIp(ip);
}

const string EngineInterface::client_getUsername() const
{
	return _core->getNetworkingClient()->getUsername();
}

const string EngineInterface::client_getServerIp() const
{
	return _core->getNetworkingClient()->getServerIp();
}

const vector<NetworkingServerMessage> EngineInterface::client_getPendingMessages() const
{
	return _core->getNetworkingClient()->getPendingMessages();
}