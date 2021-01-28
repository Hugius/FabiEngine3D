#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dTerrainEntity()
{
	// Check if entity exists
	if (_fe3d.terrainEntity_getSelectedID().empty())
	{
		_throwScriptError("Current scene has no terrain entity!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dTerrainEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:terrain_get_cursor_position") // Get the cursor position on the terrain
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				auto result = _fe3d.terrainEntity_getCursorPosition3D();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}