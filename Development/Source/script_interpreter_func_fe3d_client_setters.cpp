#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dClientSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:client_start")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.networkClient_start(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:client_connect")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.networkClient_connect(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:client_disconnect")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.networkClient_disconnect();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:client_stop")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.networkClient_stop();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:client_send_tcp_message")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.networkClient_sendMessageTCP(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:client_send_udp_message")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.networkClient_sendMessageUDP(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute client functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:client` functionality as a networking server!");
	}

	return true;
}