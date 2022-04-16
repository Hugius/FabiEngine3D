#include "script_interpreter.hpp"
#include "configuration.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dServerSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:server_start")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				_throwRuntimeError("networking server can only be started as exported application");
				return true;
			}
			if(!_isExecutingInitialization)
			{
				_throwRuntimeError("networking server can only be started in an initialization script");
				return true;
			}
			if(_engineFunctionCallCount > 0)
			{
				_throwRuntimeError("networking server can only be started before any other fe3d function call");
				return true;
			}
			if(_fe3d->server_isRunning())
			{
				_throwRuntimeError("networking server is already running");
				return true;
			}
			if(args[0]->getInteger() <= 0)
			{
				_throwRuntimeError("client count is too high");
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
				_throwRuntimeError("networking server is not running");
				return true;
			}

			_fe3d->application_stop();

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
				_throwRuntimeError("networking server is not running");
				return true;
			}
			if(find(args[1]->getString().begin(), args[1]->getString().end(), ';') != args[1]->getString().end())
			{
				_throwRuntimeError("message cannot contain ':'");
				return true;
			}
			if(_fe3d->server_isMessageReserved(args[1]->getString()))
			{
				_throwRuntimeError("message is reserved");
				return true;
			}
			if(args[1]->getString().size() > _fe3d->server_getMaxMessageSize())
			{
				_throwRuntimeError("message is too long");
				return true;
			}
			if(!_fe3d->server_isClientConnected(args[0]->getString()))
			{
				_throwRuntimeError("networking server is not connected");
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
				_throwRuntimeError("networking server is not running");
				return true;
			}
			if(!_fe3d->server_isClientConnected(args[0]->getString()))
			{
				_throwRuntimeError("networking server is not connected");
				return true;
			}
			if(find(args[1]->getString().begin(), args[1]->getString().end(), ';') != args[1]->getString().end())
			{
				_throwRuntimeError("message cannot contain ':'");
				return true;
			}
			else if(_fe3d->server_isMessageReserved(args[1]->getString()))
			{
				_throwRuntimeError("message is reserved");
				return true;
			}
			else if(args[1]->getString().size() > _fe3d->server_getMaxMessageSize())
			{
				_throwRuntimeError("message is too long");
				return true;
			}
			if(!_fe3d->server_isClientConnected(args[0]->getString()))
			{
				_throwRuntimeError("networking server is not connected");
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
				_throwRuntimeError("networking server is not running");
				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwRuntimeError("message cannot contain ':'");
				return true;
			}
			if(_fe3d->server_isMessageReserved(args[0]->getString()))
			{
				_throwRuntimeError("message is reserved");
				return true;
			}
			if(args[0]->getString().size() > _fe3d->server_getMaxMessageSize())
			{
				_throwRuntimeError("message is too long");
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
				_throwRuntimeError("networking server is not running");
				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwRuntimeError("message cannot contain ':'");
				return true;
			}
			if(_fe3d->server_isMessageReserved(args[0]->getString()))
			{
				_throwRuntimeError("message is reserved");
				return true;
			}
			if(args[0]->getString().size() > _fe3d->server_getMaxMessageSize())
			{
				_throwRuntimeError("message is too long");
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
				_throwRuntimeError("networking server is not running");
				return true;
			}
			if(!_fe3d->server_isClientConnected(args[0]->getString()))
			{
				_throwRuntimeError("networking server is not connected");
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
				_throwRuntimeError("networking server is not running");
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
		_throwRuntimeError("cannot access `fe3d:server` functionality as networking client");
		return true;
	}

	return true;
}