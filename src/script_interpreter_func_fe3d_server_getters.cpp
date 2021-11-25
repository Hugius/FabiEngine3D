#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dServerGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:server_is_running")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.server_isRunning();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:server_is_client_connected")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto result = _fe3d.server_isClientConnected(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:server_get_new_ip")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto IP = _fe3d.server_getNewClientIP();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, IP));
		}
	}
	else if(functionName == "fe3d:server_get_new_username")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto username = _fe3d.server_getNewClientUsername();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, username));
		}
	}
	else if(functionName == "fe3d:server_get_old_ip")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto IP = _fe3d.server_getOldClientIP();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, IP));
		}
	}
	else if(functionName == "fe3d:server_get_old_username")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto username = _fe3d.server_getOldClientUsername();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, username));
		}
	}
	else if(functionName == "fe3d:server_get_connected_ips")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto IPs = _fe3d.server_getClientIPs();
			for(const auto& IP : IPs)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, IP));
			}
		}
	}
	else if(functionName == "fe3d:server_get_connected_usernames")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto usernames = _fe3d.server_getClientUsernames();
			for(const auto& username : usernames)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, username));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_protocols")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			const auto& messages = _fe3d.server_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, string((message.getProtocol() == NetworkProtocol::TCP) ? "TCP" : "UDP")));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_usernames")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			const auto& messages = _fe3d.server_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, message.getUsername()));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_contents")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			const auto& messages = _fe3d.server_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, message.getContent()));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute server functionality when client is running
	if(_fe3d.client_isRunning())
	{
		_throwScriptError("cannot access `fe3d:server` functionality as a networking client!");
	}

	return true;
}