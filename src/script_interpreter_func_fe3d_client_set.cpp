#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dClientSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:client_start")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->client_isRunning())
			{
				_throwScriptError("Networking client tried to start: already running!");
				return true;
			}
			if(args[0]->getString().empty())
			{
				_throwScriptError("Networking client tried to start: username is empty!");
				return true;
			}
			if(args[0]->getString().size() > _fe3d->client_getMaxUsernameSize())
			{
				_throwScriptError("Networking client tried to start: username is too long!");
				return true;
			}
			if(_fe3d->client_isMessageReserved(args[0]->getString()))
			{
				_throwScriptError("Networking client tried to start: username is reserved!");
				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwScriptError("Networking client tried to start: username cannot contain ':'!");
				return true;
			}

			_fe3d->client_start(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_connect")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwScriptError("Networking client tried to connect: not running!");
				return true;
			}
			if(_fe3d->client_isConnectedToServer())
			{
				_throwScriptError("Networking client tried to connect: already connected!");
				return true;
			}
			if(_fe3d->client_isConnectingToServer())
			{
				_throwScriptError("Networking client tried to connect: already connecting!");
				return true;
			}
			if(!_fe3d->client_isValidServerIP(args[0]->getString()))
			{
				_throwScriptError("Networking client tried to connect: invalid server IP!");
				return true;
			}

			_fe3d->client_connect(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_disconnect")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwScriptError("Networking client tried to disconnect: not running!");
				return true;
			}
			if(!_fe3d->client_isConnectedToServer())
			{
				_throwScriptError("Networking client tried to disconnect: not connected!");
				return true;
			}
			if(!_fe3d->client_isAcceptedByServer())
			{
				_throwScriptError("Networking client tried to disconnect: not accepted!");
				return true;
			}

			_fe3d->client_disconnect();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_stop")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwScriptError("Networking client tried to stop: not running!");
				return true;
			}

			_fe3d->client_stop();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_send_tcp_message")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwScriptError("Networking client tried to send TCP message: not running!");
				return true;
			}
			if(!_fe3d->client_isConnectedToServer())
			{
				_throwScriptError("Networking client tried to send TCP message: not connected!");
				return true;
			}
			if(!_fe3d->client_isAcceptedByServer())
			{
				_throwScriptError("Networking client tried to send TCP message: not accepted!");
				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwScriptError("Networking client tried to send TCP message: cannot contain ':'!");
				return true;
			}
			if(_fe3d->client_isMessageReserved(args[0]->getString()))
			{
				_throwScriptError("Networking client tried to send TCP message: \"" + args[0]->getString() + "\" is reserved!");
				return true;
			}
			if(args[0]->getString().size() > _fe3d->client_getMaxMessageSize())
			{
				_throwScriptError("Networking client tried to send TCP message: maximum character amount exceeded!");
				return true;
			}

			_fe3d->client_sendTcpMessage(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_send_udp_message")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_fe3d->client_isRunning())
			{
				_throwScriptError("Networking client tried to send UDP message: not running!");
				return true;
			}
			if(!_fe3d->client_isConnectedToServer())
			{
				_throwScriptError("Networking client tried to send UDP message: not connected!");
				return true;
			}
			if(!_fe3d->client_isAcceptedByServer())
			{
				_throwScriptError("Networking client tried to send UDP message: not accepted!");
				return true;
			}
			if(find(args[0]->getString().begin(), args[0]->getString().end(), ';') != args[0]->getString().end())
			{
				_throwScriptError("Networking client tried to send UDP message: cannot contain ':'!");
				return true;
			}
			if(_fe3d->client_isMessageReserved(args[0]->getString()))
			{
				_throwScriptError("Networking client tried to send UDP message: \"" + args[0]->getString() + "\" is reserved!");
				return true;
			}
			if(args[0]->getString().size() > _fe3d->client_getMaxMessageSize())
			{
				_throwScriptError("Networking client tried to send UDP message: maximum character amount exceeded!");
				return true;
			}

			_fe3d->client_sendUdpMessage(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
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