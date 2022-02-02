#include "script_interpreter.hpp"
#include "configuration.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dServerSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:server_start")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_isExecutingInitialization)
			{
				_throwScriptError("networking server can only be started in initialization script!");
				return true;
			}
			if(_engineFunctionCallCount > 0)
			{
				_throwScriptError("networking server can only be started before any other fe3d function call!");
				return true;
			}
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("Networking server tried to start: already running!");
				return true;
			}
			if(args[0]->getInteger() <= 0)
			{
				_throwScriptError("Networking server tried to start: invalid maximum client count!");
				return true;
			}

			_fe3d->server_start(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_stop")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_fe3d->server_isRunning())
			{
				_throwScriptError("Networking server tried to start: already running!");
				return true;
			}

			if(Config::getInst().isApplicationExported())
			{
				_fe3d->application_stop();
			}
			else
			{
				_mustStopApplication = true;
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_send_tcp_message")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->server_isRunning())
			{
				_throwScriptError("Networking server tried to send TCP message to client \"" + args[0]->getString() + "\": not running!");
				return true;
			}
			if(find(args[1]->getString().begin(), args[1]->getString().end(), ';') != args[1]->getString().end())
			{
				_throwScriptError("Networking message tried to send TCP message: cannot contain ':'!");
				return true;
			}
			if(_fe3d->server_isMessageReserved(args[1]->getString()))
			{
				_throwScriptError("Networking server tried to send TCP message: \"" + args[1]->getString() + "\" is reserved!");
				return true;
			}
			if(args[1]->getString().size() > _fe3d->server_getMaxMessageSize())
			{
				_throwScriptError("Networking server tried to send TCP message: maximum character amount exceeded!");
				return true;
			}
			if(!_fe3d->server_isClientConnected(args[0]->getString()))
			{
				_throwScriptError("Networking server tried to send TCP message to client \"" + args[0]->getString() + "\": not connected!");
				return true;
			}

			_fe3d->server_sendTcpMessageToClient(args[0]->getString(), args[1]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_send_udp_message")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->server_isRunning())
			{
				_throwScriptError("Networking server tried to send UDP message to client \"" + args[0]->getString() + "\": not running!");
				return true;
			}
			if(!_fe3d->server_isClientConnected(args[0]->getString()))
			{
				_throwScriptError("Networking server tried to send UDP message to client \"" + args[0]->getString() + "\": not connected!");
				return true;
			}
			if(find(args[1]->getString().begin(), args[1]->getString().end(), ';') != args[1]->getString().end())
			{
				_throwScriptError("Networking message tried to send UDP message: cannot contain ':'!");
				return true;
			}
			else if(_fe3d->server_isMessageReserved(args[1]->getString()))
			{
				_throwScriptError("Networking server tried to send UDP message: \"" + args[1]->getString() + "\" is reserved!");
				return true;
			}
			else if(args[1]->getString().size() > _fe3d->server_getMaxMessageSize())
			{
				_throwScriptError("Networking server tried to send UDP message: maximum character amount exceeded!");
				return true;
			}
			if(!_fe3d->server_isClientConnected(args[0]->getString()))
			{
				_throwScriptError("Networking server tried to send UDP message to client \"" + args[0]->getString() + "\": not connected!");
				return true;
			}

			_fe3d->server_sendUdpMessageToClient(args[0]->getString(), args[1]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_broadcast_tcp_message")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->server_isRunning())
			{
				_throwScriptError("Networking server tried to broadcast TCP message: not running!");
				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwScriptError("Networking message tried to send TCP message: cannot contain ':'!");
				return true;
			}
			if(_fe3d->server_isMessageReserved(args[0]->getString()))
			{
				_throwScriptError("Networking server tried to send TCP message: \"" + args[0]->getString() + "\" is reserved!");
				return true;
			}
			if(args[0]->getString().size() > _fe3d->server_getMaxMessageSize())
			{
				_throwScriptError("Networking server tried to send TCP message: maximum character amount exceeded!");
				return true;
			}

			_fe3d->server_broadcastTcpMessageToClients(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_broadcast_udp_message")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->server_isRunning())
			{
				_throwScriptError("Networking server tried to broadcast UDP message: not running!");
				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwScriptError("Networking message tried to send UDP message: cannot contain ':'!");
				return true;
			}
			if(_fe3d->server_isMessageReserved(args[0]->getString()))
			{
				_throwScriptError("Networking server tried to send UDP message: \"" + args[0]->getString() + "\" is reserved!");
				return true;
			}
			if(args[0]->getString().size() > _fe3d->server_getMaxMessageSize())
			{
				_throwScriptError("Networking server tried to send UDP message: maximum character amount exceeded!");
				return true;
			}

			_fe3d->server_broadcastUdpMessageToClients(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_disconnect_client")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->server_isRunning())
			{
				_throwScriptError("Networking server tried to disconnect client \"" + args[0]->getString() + "\": not running!");
				return true;
			}
			if(!_fe3d->server_isClientConnected(args[0]->getString()))
			{
				_throwScriptError("Networking server tried to disconnect client \"" + args[0]->getString() + "\": not connected!");
				return true;
			}

			_fe3d->server_disconnectClient(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_disconnect_clients")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_fe3d->server_isRunning())
			{
				_throwScriptError("Networking server tried to disconnect clients: not running!");
				return true;
			}

			_fe3d->server_disconnectClients();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->client_isRunning())
	{
		_throwScriptError("cannot access `fe3d:server` functionality as networking client!");
	}

	return true;
}