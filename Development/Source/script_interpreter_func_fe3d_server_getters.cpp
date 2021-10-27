#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dServerGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:server_is_running")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.networkServer_isRunning();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:server_is_client_connected")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			auto result = _fe3d.networkServer_isClientConnected(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:server_get_new_ip")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto IP = _fe3d.networkServer_getNewClientIP();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, IP));
		}
	}
	else if(functionName == "fe3d:server_get_new_port")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto port = _fe3d.networkServer_getNewClientPort();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, port));
		}
	}
	else if(functionName == "fe3d:server_get_new_username")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto username = _fe3d.networkServer_getNewClientUsername();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, username));
		}
	}
	else if(functionName == "fe3d:server_get_old_ip")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto IP = _fe3d.networkServer_getOldClientIP();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, IP));
		}
	}
	else if(functionName == "fe3d:server_get_old_port")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto port = _fe3d.networkServer_getOldClientPort();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, port));
		}
	}
	else if(functionName == "fe3d:server_get_old_username")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto username = _fe3d.networkServer_getOldClientUsername();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, username));
		}
	}
	else if(functionName == "fe3d:server_get_connected_ips")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto IPs = _fe3d.networkServer_getClientIPs();
			for(const auto& IP : IPs)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, IP));
			}
		}
	}
	else if(functionName == "fe3d:server_get_connected_ports")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto ports = _fe3d.networkServer_getClientPorts();
			for(const auto& port : ports)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, port));
			}
		}
	}
	else if(functionName == "fe3d:server_get_connected_usernames")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto usernames = _fe3d.networkServer_getClientUsernames();
			for(const auto& username : usernames)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, username));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_ips")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto messages = _fe3d.networkServer_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, message.IP));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_ports")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto messages = _fe3d.networkServer_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, message.port));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_usernames")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto messages = _fe3d.networkServer_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, message.username));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_protocols")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto messages = _fe3d.networkServer_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, string((message.protocol == NetworkProtocol::TCP) ? "TCP" : "UDP")));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_contents")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto messages = _fe3d.networkServer_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, message.content));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute server functionality when client is running
	if(_fe3d.networkClient_isRunning())
	{
		_throwScriptError("cannot access `fe3d:server` functionality as a networking client!");
	}

	return true;
}