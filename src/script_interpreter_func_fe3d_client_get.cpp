#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dClientGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:client_is_valid_server_ip")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = _fe3d->client_isValidServerIP(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_is_running")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->client_isRunning();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_is_connecting")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_core->getNetworkingClient()->isRunning())
			{
				Logger::throwWarning("Networking client tried to get connecting status: not running!");
				return false;
			}

			const auto result = _fe3d->client_isConnectingToServer();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_is_connected")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_core->getNetworkingClient()->isRunning())
			{
				Logger::throwWarning("Networking client tried to get connection status: not running!");
				return false;
			}

			const auto result = _fe3d->client_isConnectedToServer();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_is_accepted")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_core->getNetworkingClient()->isRunning())
			{
				Logger::throwWarning("Networking client tried to get pending messages: not running!");
				return {};
			}

			const auto result = _fe3d->client_isAcceptedByServer();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_get_pending_protocols")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_core->getNetworkingClient()->isRunning())
			{
				Logger::throwWarning("Networking client tried to get pending messages: not running!");
				return {};
			}

			for(const auto& message : _fe3d->client_getPendingMessages())
			{
				const auto result = string((message.getProtocol() == NetworkProtocol::TCP) ? "TCP" : "UDP");

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:client_get_pending_contents")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_core->getNetworkingClient()->isRunning())
			{
				Logger::throwWarning("Networking client tried to get pending messages: not running!");
				return {};
			}

			for(const auto& message : _fe3d->client_getPendingMessages())
			{
				const auto result = message.getContent();

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:client_get_ping_latency")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_core->getNetworkingClient()->isRunning())
			{
				Logger::throwWarning("Networking client tried to get ping latency: not running!");
				return 0;
			}
			if(!_core->getNetworkingClient()->isConnectedToServer())
			{
				Logger::throwWarning("Networking client tried to get ping latency: not connected!");
				return 0;
			}
			if(!_core->getNetworkingClient()->isAcceptedByServer())
			{
				Logger::throwWarning("Networking client tried to get ping latency: not accepted!");
				return 0;
			}

			const auto result = _fe3d->client_getPingLatency();

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:client_get_server_ip")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_core->getNetworkingClient()->isRunning())
			{
				Logger::throwWarning("Networking client tried to get server IP: not running!");
				return "";
			}
			if(!_core->getNetworkingClient()->isConnectedToServer())
			{
				Logger::throwWarning("Networking client tried to get server IP: not connected!");
				return "";
			}
			if(!_core->getNetworkingClient()->isAcceptedByServer())
			{
				Logger::throwWarning("Networking client tried to get server IP: not accepted!");
				return "";
			}

			const auto result = _fe3d->client_getServerIP();

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:client_get_username")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_core->getNetworkingClient()->isRunning())
			{
				Logger::throwWarning("Networking client tried to get username: not running!");
				return "";
			}

			const auto result = _fe3d->client_getUsername();

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:client` functionality as networking server!");
	}

	return true;
}