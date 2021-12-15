#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dClientSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:client_start")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.client_start(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_connect")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.client_connect(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_disconnect")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.client_disconnect();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_stop")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.client_stop();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_send_tcp_message")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.client_sendTcpMessage(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:client_send_udp_message")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.client_sendUdpMessage(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:client` functionality as networking server!");
	}

	return true;
}