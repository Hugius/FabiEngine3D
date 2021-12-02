#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dServerSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:server_start")
	{
		auto types = {SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// CoreEngine must know if application is a networking server, so server can only be started in initialization phase
			if(!_isExecutingInitialization)
			{
				_throwScriptError("networking server can only be started in initialization script!");
				return true;
			}

			// Server startup must be the first function called
			if(_engineFunctionCallCount > 0)
			{
				_throwScriptError("networking server can only be started before any other fe3d function call!");
				return true;
			}

			// Start server
			_fe3d.server_start(arguments[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_send_tcp_message")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.server_sendMessageTCP(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_send_udp_message")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.server_sendMessageUDP(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_broadcast_tcp_message")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.server_broadcastMessageTCP(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_broadcast_udp_message")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.server_broadcastMessageUDP(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_disconnect_client")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.server_disconnectClient(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:server_disconnect_clients")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.server_disconnectClients();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute server functionality when client is running
	if(_fe3d.client_isRunning())
	{
		_throwScriptError("cannot access `fe3d:server` functionality as networking client!");
	}

	return true;
}