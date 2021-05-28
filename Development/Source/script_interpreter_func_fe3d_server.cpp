#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dServerFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:network_server_start")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{			
			_fe3d.networkServer_start();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:network_server_stop")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.networkServer_stop();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:network_server_is_started")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.networkServer_isStarted();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:network_server_is_message_pending")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.networkServer_isMessagePending();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:network_server_get_message_ip_address")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.networkServer_getPendingMessage();
			if (result != nullptr)
			{
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result->ipAddress));
			}
		}
	}
	else if (functionName == "fe3d:network_server_get_message_port")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.networkServer_getPendingMessage();
			if (result != nullptr)
			{
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result->port));
			}
		}
	}
	else if (functionName == "fe3d:network_server_get_message_content")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.networkServer_getPendingMessage();
			if (result != nullptr)
			{
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result->content));
			}
		}
	}
	else if (functionName == "fe3d:network_server_load_next_message")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.networkServer_loadNextPendingMessage();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:network_server_send_message")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.networkServer_sendMessage(arguments[0].getString(), arguments[1].getString(), arguments[2].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:network_server_broadcast_message")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.networkServer_broadcastMessage(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}