#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dNetworkFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:networking_start")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{			
			// Determine peer type
			if (arguments[0].getString() == "SERVER")
			{
				_fe3d.network_start(NetworkPeerType::SERVER);
			}
			else if (arguments[0].getString() == "CLIENT")
			{
				_fe3d.network_start(NetworkPeerType::CLIENT);
			}
			else
			{
				_throwScriptError("invalid peer type!");
				return true;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:networking_stop")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.network_stop();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:networking_is_message_pending")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.network_isMessagePending();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:networking_get_message_ip")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.network_getPendingMessage()->ipAddress;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:networking_get_message_content")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.network_getPendingMessage();
			if (result != nullptr)
			{
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result->content));
			}
		}
	}
	else if (functionName == "fe3d:networking_load_next_message")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.network_loadNextPendingMessage();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}