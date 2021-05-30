#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dServerFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:network_server_start")
	{
		auto types = { ScriptValueType::INTEGER };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// CoreEngine must know if application is a network server
			if (!_isExecutingInitialization)
			{
				_throwScriptError("network server can only be started in initialization script!");
				return true;
			}

			// Start server
			_fe3d.networkServer_start(arguments[0].getInteger());
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
	else if (functionName == "fe3d:network_server_is_connected")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			auto result = _fe3d.networkServer_isClientConnected(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:network_server_send_message")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			NetworkMessage message = NetworkMessage(arguments[0].getString(), arguments[1].getString(), arguments[2].getString());
			_fe3d.networkServer_sendMessage(message);
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
	else if (functionName == "fe3d:network_server_get_pending_ips")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto messages = _fe3d.networkServer_getPendingMessages();
			for (const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, message.ipAddress));
			}
		}
	}
	else if (functionName == "fe3d:network_server_get_pending_ports")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto messages = _fe3d.networkServer_getPendingMessages();
			for (const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, message.port));
			}
		}
	}
	else if (functionName == "fe3d:network_server_get_pending_messages")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto messages = _fe3d.networkServer_getPendingMessages();
			for (const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, message.content));
			}
		}
	}
	else if (functionName == "fe3d:network_server_get_client_ips")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto IPs = _fe3d.networkServer_getClientIPs();
			for (const auto& IP : IPs)
			{
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, IP));
			}
		}
	}
	else if (functionName == "fe3d:network_server_get_client_ports")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto ports = _fe3d.networkServer_getClientPorts();
			for (const auto& port : ports)
			{
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, port));
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}