#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::client_start(const string& username)
{
	_core->getNetworkingClient()->start(username);
}

void EngineInterface::client_connect(const string& serverIP)
{
	_core->getNetworkingClient()->connectToServer(serverIP);
}

void EngineInterface::client_sendTcpMessage(const string& content)
{
	_core->getNetworkingClient()->sendTcpMessage(content);
}

void EngineInterface::client_sendUdpMessage(const string& content)
{
	_core->getNetworkingClient()->sendUdpMessage(content);
}

void EngineInterface::client_disconnect()
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

const bool EngineInterface::client_isValidServerIP(const string& serverIP) const
{
	return _core->getNetworkingClient()->isValidServerIP(serverIP);
}

const string EngineInterface::client_getUsername() const
{
	return _core->getNetworkingClient()->getUsername();
}

const string EngineInterface::client_getServerIP() const
{
	return _core->getNetworkingClient()->getServerIP();
}

const vector<NetworkingServerMessage> EngineInterface::client_getPendingMessages() const
{
	return _core->getNetworkingClient()->getPendingMessages();
}