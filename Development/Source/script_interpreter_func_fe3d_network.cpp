#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dNetworkFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:networking_enable")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			if (arguments[0].getString() == "SERVER")
			{
				_fe3d.network_enable(NetworkPeerType::SERVER);
			}
			else if (arguments[0].getString() == "CLIENT")
			{
				_fe3d.network_enable(NetworkPeerType::CLIENT);
			}
			else
			{
				_throwScriptError("invalid peer type!");
				return true;
			}

			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}