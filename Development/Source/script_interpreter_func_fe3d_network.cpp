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
			// Validate networking status
			if (_fe3d.network_isStarted())
			{
				_throwScriptError("networking is already started!");
				return true;
			}
			
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
			// Validate networking status
			if (!_fe3d.network_isStarted())
			{
				_throwScriptError("networking is not started!");
				return true;
			}

			// Stop networking
			_fe3d.network_stop();

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}