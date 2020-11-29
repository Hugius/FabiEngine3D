#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dGameEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:raycast_in_entity") // Raycasting into a single entity
	{
		auto types = { ScriptValueType::STRING };

		if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
		{
			auto result = _fe3d.collision_checkCursorInEntity(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			return true;
		}
	}
	else
	{
		return false;
	}
}