#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dClientSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:client_start")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->client_isRunning())
			{
				_throwRuntimeError("networking client is already running");

				return true;
			}
			if(args[0]->getString().empty())
			{
				_throwRuntimeError("username is empty");

				return true;
			}
			if(args[0]->getString().size() > _fe3d->client_getMaxUsernameSize())
			{
				_throwRuntimeError("username is too long");

				return true;
			}
			if(_fe3d->client_isMessageReserved(args[0]->getString()))
			{
				_throwRuntimeError("username is reserved");

				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwRuntimeError("username cannot contain ':'");

				return true;
			}

			_fe3d->client_start(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_connect")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwRuntimeError("networking client is not running");

				return true;
			}
			if(_fe3d->client_isConnectedToServer())
			{
				_throwRuntimeError("networking client is already connected");

				return true;
			}
			if(_fe3d->client_isConnectingToServer())
			{
				_throwRuntimeError("networking client is already connecting");

				return true;
			}
			if(!_fe3d->client_isValidIp(args[0]->getString()))
			{
				_throwRuntimeError("server IP is invalid");

				return true;
			}

			_fe3d->client_connectToServer(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_disconnect")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwRuntimeError("networking client is not running");

				return true;
			}
			if(!_fe3d->client_isConnectedToServer())
			{
				_throwRuntimeError("networking client is not connected");

				return true;
			}
			if(!_fe3d->client_isAcceptedByServer())
			{
				_throwRuntimeError("networking client is not accepted");

				return true;
			}

			_fe3d->client_disconnectFromServer();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_stop")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwRuntimeError("networking client is not running");

				return true;
			}

			_fe3d->client_stop();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_send_tcp_message")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwRuntimeError("networking client is not running");

				return true;
			}
			if(!_fe3d->client_isConnectedToServer())
			{
				_throwRuntimeError("networking client is not connected");

				return true;
			}
			if(!_fe3d->client_isAcceptedByServer())
			{
				_throwRuntimeError("networking client is not accepted");

				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwRuntimeError("message cannot contain ':'");

				return true;
			}
			if(_fe3d->client_isMessageReserved(args[0]->getString()))
			{
				_throwRuntimeError("message is reserved");

				return true;
			}
			if(args[0]->getString().size() > _fe3d->client_getMaxMessageSize())
			{
				_throwRuntimeError("message is too long");

				return true;
			}

			_fe3d->client_sendTcpMessageToServer(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_send_udp_message")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwRuntimeError("networking client is not running");

				return true;
			}
			if(!_fe3d->client_isConnectedToServer())
			{
				_throwRuntimeError("networking client is not connected");

				return true;
			}
			if(!_fe3d->client_isAcceptedByServer())
			{
				_throwRuntimeError("networking client is not accepted");

				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwRuntimeError("message cannot contain ':'");

				return true;
			}
			if(_fe3d->client_isMessageReserved(args[0]->getString()))
			{
				_throwRuntimeError("message is reserved");

				return true;
			}
			if(args[0]->getString().size() > _fe3d->client_getMaxMessageSize())
			{
				_throwRuntimeError("message is too long");

				return true;
			}

			_fe3d->client_sendUdpMessageToServer(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:client` functionality as a networking server");

		return true;
	}

	return true;
}